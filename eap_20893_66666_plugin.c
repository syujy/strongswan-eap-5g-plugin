#include "eap_20893_66666_plugin.h"

#include "eap_20893_66666.h"

#include <daemon.h>

METHOD(plugin_t, get_name, char*,
	eap_20893_66666_plugin_t *this)
{
	return "eap-20893-66666";
}

METHOD(plugin_t, get_features, int,
	eap_20893_66666_plugin_t *this, plugin_feature_t *features[])
{
	static plugin_feature_t f[] = {
		PLUGIN_CALLBACK(eap_method_register, eap_20893_66666_create_server),
			PLUGIN_PROVIDE(EAP_SERVER_VENDOR, 20893, 66666),
		PLUGIN_CALLBACK(eap_method_register, eap_20893_66666_create_peer),
			PLUGIN_PROVIDE(EAP_PEER_VENDOR, 20893, 66666),
	};
	*features = f;
	return countof(f);
}

METHOD(plugin_t, destroy, void,
	eap_20893_66666_plugin_t *this)
{
	free(this);
}

/*
 * see header file
 */
plugin_t *eap_20893_66666_plugin_create()
{
	eap_20893_66666_plugin_t *this;

	INIT(this,
		.plugin = {
			.get_name = _get_name,
			.get_features = _get_features,
			.destroy = _destroy,
		},
	);

	return &this->plugin;
}

