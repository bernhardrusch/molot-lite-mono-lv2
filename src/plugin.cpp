#include <new>
#include "molot_lite_mono.h"

#define SIZEOF_URI_STRING 20
#define SIZEOF_EXT_URI_STRING 25

// Our own URI we made up for our plugin. Must match the one in our TTL file
static const char UriStr[] = URI_STRING;

static const char MapUriStr[] = "http://lv2plug.in/ns/ext/urid#map";





/*************************** run() ***************************
 * Called by host to add DSP to the waveform data in the
 * input buffer(s), and stores the new data in the output
 * buffer(s).
 *
 * instance = Ptr to our MolotLiteMono.
 * sampleFrames =	How many floats to process per channel.
 */

static void run(LV2_Handle instance, uint32_t sampleFrames)
{
	register MolotLiteMono *	plugin;

	if ((plugin = static_cast<MolotLiteMono *> (instance)))
	{
		plugin->Host.Begin = 0;

		plugin->Host.End = sampleFrames - plugin->Host.Begin;
		plugin->pluginRun();
	}
}





/************************* cleanup() **************************
 * Called by host to free the plugin instance (i.e. the
 * MolotLiteMono gotten via instantiate()).
 *
 * instance =	Our own MolotLiteMono.
 */

static void cleanup(LV2_Handle instance)
{
	if (instance)
	{
		// Get rid of the MolotLiteMono
		{
		register MolotLiteMono * plugin;

		plugin = static_cast<MolotLiteMono *> (instance);
		delete plugin;
		}
	}
}





/*********************** instantiate() ************************
 * Called by host to alloc/init a new plugin instance.
 *
 * RETURNS: If success, a pointer to our own MolotLiteMono
 * that holds all data needed to implement our plugin.
 */

static LV2_Handle instantiate(const LV2_Descriptor * descriptor, double rate, const char * path, const LV2_Feature * const * features)
{
	register MolotLiteMono *	plugin;

	// Create an instance of MolotLiteMono (defined in Molot_Mono_Lite.h)
	plugin = new (std::nothrow) MolotLiteMono((double)rate);
	if (plugin)
	{
		plugin->Host.SampleRate = (float)rate;

	}

	// Return our MolotLiteMono to the host (and the
	// host passes back to our functions)
	return (LV2_Handle)plugin;
}





/************************ activate() *************************
 * Called by host to reset the state of a plugin, once before
 * our host starts making multiple calls to our run function.
 *
 * instance =	Our own MolotLiteMono.
 */

static void activate(LV2_Handle instance)
{
	register MolotLiteMono *	plugin;

	if ((plugin = static_cast<MolotLiteMono *> (instance))) plugin->pluginActivate();
}





/*********************** deActivate() ************************
 * Called by host once after done making multiple calls to our
 * run function.
 *
 * instance =	Our own MolotLiteMono.
 */

static void deActivate(LV2_Handle instance)
{
	register MolotLiteMono *	plugin;

	if ((plugin = static_cast<MolotLiteMono *> (instance))) plugin->pluginDeActivate();
}





/*********************** connectPort() ************************
 * Called by host to connect a port to a data location (ie, allow
 * us to store a pointer to a host-supplied data or buffer. NOTE:
 * all host data is a float).
 *
 * instance =	Our own MolotLiteMono.
 * port =		Indicates what hostData is being supplied.
 * hostData =	Pointer to host float data, or buffer of floats.
 */

static void connectPort(LV2_Handle instance, uint32_t port, void * hostData)
{
	register MolotLiteMono *	plugin;

	plugin = static_cast<MolotLiteMono *> (instance);
	if (plugin && port < LV2_NUM_ALL_PORTS)
	{
				if (port < LV2_NUM_AUDIO_INS)
			plugin->Host.AudioIn[port] = (float *)hostData;
		else
		{
			port -= LV2_NUM_AUDIO_INS;
			if (port < LV2_NUM_AUDIO_OUTS)
				plugin->Host.AudioOut[port] = (float *)hostData;
			else
			{
				port -= LV2_NUM_AUDIO_OUTS;
				plugin->Host.In[port] = (float *)hostData;
			}
		}
	}
}





/********************* lv2_descriptor() **********************
 * Returns a pointer to our LV2_Descriptor struct at the
 * requested index.
 *
 * index =	The plugin index.
 *
 * NOTE: "index" ranges from 0 to how many plugins we support
 * (minus 1). For this example, we have 1 plugin. We'll assign an
 * index of 0 for it. Any other index values, we return a 0 to
 * indicate we have no further plugin types.
 *
 * This function must be named "lv2_descriptor", and can't be
 * static. Our plugin must contain this function.
 */

static const LV2_Descriptor PluginDescriptor = {
	UriStr,
	instantiate,
	connectPort,
	activate,
	run,
	deActivate,
	cleanup,
	NULL};

LV2_SYMBOL_EXPORT const LV2_Descriptor * lv2_descriptor(uint32_t index)
{
	if (!index) return &PluginDescriptor;
	return 0;
}
