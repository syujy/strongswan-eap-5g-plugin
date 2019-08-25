/**
 * @defgroup eap_20893_66666_i eap_20893_66666
 * @{ @ingroup eap_20893_66666
 */

#ifndef EAP_20893_66666_H_
#define EAP_20893_66666_H_

typedef struct eap_20893_66666_t eap_20893_66666_t;

#include <sa/eap/eap_method.h>

/**
 * Implementation of the eap_method_t interface using EAP-20893-66666.
 *
 * This implementation of draft-sheffer-ikev2-20893-66666-00.txt uses PAM to
 * verify user credentials.
 */
struct eap_20893_66666_t {

	/**
	 * Implemented eap_method_t interface.
	 */
	eap_method_t eap_method_interface;
};

/**
 * Creates the EAP method EAP-20893-66666 acting as server.
 *
 * @param server	ID of the EAP server
 * @param peer		ID of the EAP client
 * @return			eap_20893_66666_t object
 */
eap_20893_66666_t *eap_20893_66666_create_server(identification_t *server, identification_t *peer);

/**
 * Creates the EAP method EAP-20893-66666 acting as peer.
 *
 * @param server	ID of the EAP server
 * @param peer		ID of the EAP client
 * @return			eap_20893_66666_t object
 */
eap_20893_66666_t *eap_20893_66666_create_peer(identification_t *server, identification_t *peer);

#endif /** EAP_20893_66666_H_ @}*/
