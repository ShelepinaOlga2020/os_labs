#include <vector>
#include <list>
#include <shared_mutex>
#include <thread>
#include <iostream>
#define FULL 100
using namespace std;

void Pr(int time);
void Con(int time);
void Print();
bool Empty(std::unique_lock<std::mutex>& lock);
bool Full(std::unique_lock<std::mutex>& lock);

std::mutex _access;
std::vector<int> st;

int main(){
	thread t1([]() {Pr(700);  });
	thread t2([]() {Con(100);  });
	thread t3([]() {Pr(500);  });
	
	t1.join();
	t2.join();
	t3.join();

	return 1;
}

bool Full(std::unique_lock<std::mutex>& lock) {
	bool temp;
	if (st.size() == FULL) {
		temp = true;
	}
	else {
		temp = false;
	};
	return temp;
}

void Print(){
	for (int i = 0; i < st.size(); i++){
		cout << st[i] << "\t";
	}cout << endl;
}


bool Empty(std::unique_lock<std::mutex>& lock){
	bool temp = st.empty();
	return temp;
};



void Con(int time) {
	std::unique_lock<std::mutex> lock(_access, defer_lock);

	while (true) {
		lock.lock();
		if (!Empty(lock)) {
			st.pop_back();
			cout << "Con " << this_thread::get_id() << " :: ";
			Print();
		}
		lock.unlock();
		this_thread::sleep_for(chrono::milliseconds(time));
	};

}
void Pr(int time) {
	std::unique_lock<std::mutex> lock(_access, defer_lock);
	lock.lock();
	cout << this_thread::get_id() << " PR START" << endl;
	lock.unlock();


	while (true) {
		lock.lock();
		if (!Full(lock)) {
			st.push_back(5);
			cout << "PR " << this_thread::get_id() << " :: ";
			Print();
		}
		lock.unlock();
		this_thread::sleep_for(chrono::milliseconds(time));
	}

	lock.lock();
	cout << this_thread::get_id() << " Con END" << endl;
	lock.unlock();
};

