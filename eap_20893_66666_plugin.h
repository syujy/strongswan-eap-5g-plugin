/**
 * @defgroup eap_20893_66666 eap_20893_66666
 * @ingroup cplugins
 *
 * @defgroup eap_20893_66666_plugin eap_20893_66666_plugin
 * @{ @ingroup eap_20893_66666
 */

#ifndef EAP_20893_66666_PLUGIN_H_
#define EAP_20893_66666_PLUGIN_H_

#include <plugins/plugin.h>

typedef struct eap_20893_66666_plugin_t eap_20893_66666_plugin_t;

/**
 * EAP-20893-66666 plugin
 */
struct eap_20893_66666_plugin_t {

	/**
	 * implements plugin interface
	 */
	plugin_t plugin;
};

#endif /** EAP_20893_66666_PLUGIN_H_ @}*/
