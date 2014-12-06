class TruthSwitch
{
	bool m_activated;

public:
	TruthSwitch(void) : m_activated(false) {}
	TruthSwitch(bool b) : m_activated(b) {}

	// Set the bool to true
	void Set(void) { m_activated = true; }

	// Return the bool - set it to false
	bool Read(void) 
	{ 
		if (m_activated) { 
			m_activated = false; 
			return true; 
		} 
		else return false; 
	}
};