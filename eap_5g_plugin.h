/**
 * @defgroup eap_5g eap_5g
 * @ingroup cplugins
 *
 * @defgroup eap_5g_plugin eap_5g_plugin
 * @{ @ingroup eap_5g
 */

#ifndef EAP_5G_PLUGIN_H_
#define EAP_5G_PLUGIN_H_

#include <plugins/plugin.h>

typedef struct eap_5g_plugin_t eap_5g_plugin_t;

/**
 * EAP-{type}-{vendor} plugin
 */
struct eap_5g_plugin_t {

	/**
	 * implements plugin interface
	 */
	plugin_t plugin;
};

#endif /** EAP_5G_PLUGIN_H_ @}*/
