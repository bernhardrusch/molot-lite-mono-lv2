#include "plugin.h"
#include "moloteng.h"

class MolotLiteMono
{
public:
	MolotLiteMono(double);
	~MolotLiteMono();
	void pluginRun();
	void pluginActivate();
	void pluginDeActivate();
	
	MOLOT_MONO_LITE	Host;

private:
	MonoCompressor		m_comp;
	double				Value[LV2_NUM_INS];

	void UpdateParameters();
};
