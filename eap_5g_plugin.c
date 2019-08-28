#include "eap_5g_plugin.h"

#include "eap_5g.h"

#include <daemon.h>

METHOD(plugin_t, get_name, char*,
	eap_5g_plugin_t *this)
{
	return "eap-VENDOR_TYPE-VENDOR_ID";
}

METHOD(plugin_t, get_features, int,
	eap_5g_plugin_t *this, plugin_feature_t *features[])
{
	static plugin_feature_t f[] = {
		PLUGIN_CALLBACK(eap_method_register, eap_5g_create_server),
			PLUGIN_PROVIDE(EAP_SERVER_VENDOR, VENDOR_TYPE, VENDOR_ID),
		PLUGIN_CALLBACK(eap_method_register, eap_5g_create_peer),
			PLUGIN_PROVIDE(EAP_PEER_VENDOR, VENDOR_TYPE, VENDOR_ID),
	};
	*features = f;
	return countof(f);
}

METHOD(plugin_t, destroy, void,
	eap_5g_plugin_t *this)
{
	free(this);
}

/*
 * see header file
 */
plugin_t *eap_5g_plugin_create()
{
	eap_5g_plugin_t *this;

	INIT(this,
		.plugin = {
			.get_name = _get_name,
			.get_features = _get_features,
			.destroy = _destroy,
		},
	);

	return &this->plugin;
}

