#pragma once

class Process {
public:
	enum class state_t {
		run,
		ready,
		done,
		not_launched
	};
private:
	int id; /*����� ��������*/
	int lead_time; /*�������, ����������� �� ����������*/
	int priority; /*���������*/
	int appearance_time; /*����� ���������*/
	int in_system_time; /*����� ����� � �������*/
	int in_run_time; /*����� ����������*/
	int cpu_time; /*������������ �����*/
	state_t state; /*��������� ��������*/

	static int get_id() { static int i = 0; return i++; }

public:
	Process(int lead_time, int priority, state_t state, int appearance_time)
		: lead_time(lead_time), priority(priority), state(state),
		appearance_time(appearance_time), id(get_id()), in_system_time(0),
		in_run_time(0), cpu_time(0) {}

	/*get*/
	int getId() const { return this->id; }
	int getLeadTime() const { return this->lead_time; }
	int getPriority() const { return this->priority; }
	int getAppearanceTime() const { return this->appearance_time; }
	int getInSystemTime() const { return this->in_system_time; }
	int getInRunTime()const { return this->in_run_time; }
	int getCpuTime() const { return this->cpu_time; }
	state_t getState() const { return this->state; }

	/*set*/
	void setState(state_t state) { this->state = state; }
	void incCpuTime(int inc) { this->cpu_time += inc; }
	void del2CpuTime() { this->cpu_time /= 2; }
	void setPriority(int priority) { this->priority = priority; }

	void update(int count_kwants)
	{
		if (count_kwants >= this->appearance_time && this->state == state_t::not_launched)
			this->state = state_t::ready;

		if (this->state == state_t::ready || this->state == state_t::run)
			this->in_system_time++;

		if (this->state == state_t::run)
			this->in_run_time++;
	}

	friend std::ostream& operator<<(std::ostream& os, state_t state)
	{
		switch (state)
		{
		case Process::state_t::run:
			os << "���-��";
			break;
		case Process::state_t::ready:
			os << "�����";
			break;
		case Process::state_t::done:
			os << "���-��";
			break;
		case Process::state_t::not_launched:
			os << "��_���";
			break;
		}
		return os;
	}
};


