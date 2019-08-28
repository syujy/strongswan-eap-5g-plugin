/**
 * @defgroup eap_5g_i eap_5g
 * @{ @ingroup eap_5g
 */

#ifndef EAP_5G_H_
#define EAP_5G_H_

typedef struct eap_5g_t eap_5g_t;

#include <sa/eap/eap_method.h>

#define VENDOR_ID 66666
#define VENDOR_TYPE 20893

/**
 * Implementation of the eap_method_t interface using EAP-{type}-{vendor}.
 *
 * This implementation follow 3GPP TS 23.502 system procedure to
 * verify user credentials.
 */
struct eap_5g_t {

	/**
	 * Implemented eap_method_t interface.
	 */
	eap_method_t eap_method_interface;
};

/**
 * Creates the EAP method EAP-{type}-{vendor} acting as server.
 *
 * @param server	ID of the EAP server
 * @param peer		ID of the EAP client
 * @return			eap_5g_t object
 */
eap_5g_t *eap_5g_create_server(identification_t *server, identification_t *peer);

/**
 * Creates the EAP method EAP-{type}-{vendor} acting as peer.
 *
 * @param server	ID of the EAP server
 * @param peer		ID of the EAP client
 * @return			eap_5g_t object
 */
eap_5g_t *eap_5g_create_peer(identification_t *server, identification_t *peer);

#endif /** EAP_5G_H_ @}*/
