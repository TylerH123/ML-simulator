#include <iostream>
#include <string>  
#include "csvstream.h" 
#include <set>
#include <math.h>

using namespace std; 

class Classifier{
public: 
	Classifier(string train, string test, bool d):
	train_file(train), test_file(test), debug(d){
		try { 
			classify();
		}
		catch (...) {
			throw string("train_error"); 
		}
		try {
			prediction(); 
		}
		catch (...) {
			throw string("test_error"); 
		}
	}
	set<string> unique_words(const string &str, set<string> &s) {
 		istringstream source(str);
 		string word;
		set<string> words; 
 		// Read word by word from the stringstream and insert into the set
 		while (source >> word) {
   			s.insert(word);
			words.insert(word);
 		}
		return words; 
	} 
	set<string> unique_words(const string &str) {
 		istringstream source(str);
 		string word;
		set<string> words; 
 		// Read word by word from the stringstream and insert into the set
 		while (source >> word) {
			words.insert(word);
 		}
		return words; 
	} 
	void classify() {
		csvstream csvin(train_file);
		map<string, string> row; 
		set<string> words;
		if (debug) 
			cout << "training data:" << "\n"; 
		while (csvin >> row) {
			if (debug) 
				cout << "  label = " << row["tag"] << ", content = " 
					 << row["content"] << "\n"; 
			set<string> row_words = unique_words(row["content"], words);
			for (auto word: row_words) {
				w_total[word]++; 
				data[{row["tag"], word}]++; 
			} 
			c_total[row["tag"]]++; 
			total_posts++; 
		}
		total_unique_words = words.size();
		cout << "trained on " << total_posts << " examples" << endl;
		if (debug) 
			cout << "vocabulary size = " << total_unique_words << "\n";  	
		cout << "\n";
		calculate_log_prior();
		calculate_log_likelihood();  
	}
	void calculate_log_prior(){
		if (debug) 
			cout << "classes:" << "\n"; 
		for (auto p : c_total) {
			double d = log((double)c_total[p.first] / total_posts);
			log_prior[p.first] = d;	
			if (debug) {
				cout << "  " << p.first << ", "  << c_total[p.first] 
					 << " examples, log-prior = " << d << "\n"; 
			}
		}
	}
	void calculate_log_likelihood() {
		if (debug) 
			cout << "classifier parameters:" << "\n"; 
		for (auto p : data) {
			double d = log((double)data[p.first] / c_total[p.first.first]); 
			log_likelihood[{p.first.first,p.first.second}] = d; 
			if (debug) {
				cout << "  " << p.first.first << ":" << p.first.second << ", count = " 
					 << data[{p.first.first, p.first.second}] << ", log-likelihood = " 
					 << d << "\n"; 
			}
		}
	}
	double get_log_likelihood(string &label, string &word){ 
		double ll = log_likelihood[{label, word}]; 
		if(ll != 0) {
			return ll;
		}
		else {
			double x = double(w_total[word]);
			if (x != 0) {
				return log(x / total_posts);
			}
			else {
				return log(1.0 / total_posts);  
			}
		}
	}

	void prediction(){
		csvstream csvin(test_file);
		map<string, string> post; 
		int correct = 0; 
		int test_total_posts = 0; 
		cout << "test data:" << "\n"; 
		while(csvin >> post){
			set<string> post_words = unique_words(post["content"]);
			pair<string, double> max = {"", 0};
			for(auto p : log_prior){
				string label = p.first;
				double d = p.second;
				for(auto word: post_words ){
					d += get_log_likelihood(label, word);
				}
				if(max.first == ""){
					max = {label, d};
				}
				if(max.second < d){
					max = {label, d};
				}
			}
			test_total_posts++;
			if (max.first == post["tag"]) 
				correct++; 
			cout << "  correct = " << post["tag"] << ", predicted = " << max.first 
			     << ", log-probability score = " << max.second << "\n"; 
			cout << "  content = " << post["content"] << "\n\n"; 
		}
		cout << "performance: " << correct << " / " << test_total_posts 
			 << " posts predicted correctly" << "\n";
	}
private: 
	// inputs
	string train_file; 
	string test_file; 
	bool debug; 
	//training data
	int total_posts = 0; 
	int total_unique_words = 0; 
	map<pair<string, string>, int> data;  
	map<string, int> w_total; 
	map<string, int> c_total; 
	map<string, double> log_prior; 
	map<pair<string,string>, double> log_likelihood; 
}; 

int main(int argc, char *argv[]) {
	cout.precision(3);
	if (argc != 3 && argc != 4) {
		cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
		return 1; 
	}
	bool debug = false; 
	if (argc == 4) {
		if (string(argv[3]) == "--debug") 
			debug = true;
		else {
			cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
			return 1; 
		}
	}
	try {
		Classifier c(argv[1],argv[2], debug); 
	}
	catch (string s) {
		if (s == "train_error") 
			cout << "Error opening file: " << argv[1] << endl;
		if (s == "test_error") 
			cout << "Error opening file: " << argv[2] << endl;
		return 1; 
	}
	return 0; 
}