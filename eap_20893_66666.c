#include "eap_20893_66666.h"

#include <daemon.h>
#include <library.h>

#define NAS_MSG "I am a test NAS packet"

typedef struct private_eap_20893_66666_t private_eap_20893_66666_t;

/**
 * Private data of an eap_20893_66666_t object.
 */
struct private_eap_20893_66666_t {

	/**
	 * Public authenticator_t interface.
	 */
	eap_20893_66666_t public;

	/**
	 * ID of the server
	 */
	identification_t *server;

	/**
	 * ID of the peer
	 */
	identification_t *peer;

	/**
	 * EAP message identififier
	 */
	uint8_t identifier;
};

typedef struct eap_20893_66666_header_t eap_20893_66666_header_t;

/**
 * packed eap 5G header struct
 */
struct eap_20893_66666_header_t {
	/** EAP code (REQUEST/RESPONSE) */
	uint8_t code;
	/** unique message identifier */
	uint8_t identifier;
	/** length of whole message */
	uint16_t length;
	/** EAP type */
	uint8_t type;
	/** vendor ID **/
	uint8_t vendor_id[3];
	/** vendor type **/
	uint32_t vendor_type;
	/** vendor data */
	uint8_t data[];
} __attribute__((__packed__));

METHOD(eap_method_t, initiate_peer, status_t,
	private_eap_20893_66666_t *this, eap_payload_t **out)
{
	/* peer never initiates */
	return FAILED;
}

#define VENDOR_ID 66666
#define VENDOR_TYPE 20893

#define SETTYPEPLUSID(addr) \
	*(uint32_t *)addr = \
	htonl(((uint32_t)EAP_EXPANDED << 24) | \
	(VENDOR_ID))

METHOD(eap_method_t, initiate_server, status_t,
	private_eap_20893_66666_t *this, eap_payload_t **out)
{
	eap_20893_66666_header_t *req;
	size_t len;

	len = sizeof(eap_20893_66666_header_t) + strlen(NAS_MSG);
	req = alloca(len);
	req->length = htons(len);
	req->code = EAP_REQUEST;
	req->identifier = this->identifier;
	SETTYPEPLUSID(&req->type);
	req->vendor_type = htonl(VENDOR_TYPE);
	memcpy(req->data, NAS_MSG, strlen(NAS_MSG));

	*out = eap_payload_create_data(chunk_create((void*)req, len));

	return NEED_MORE;
}

METHOD(eap_method_t, process_peer, status_t,
        private_eap_20893_66666_t *this, eap_payload_t *in, eap_payload_t **out)
{
        eap_20893_66666_header_t *res;
        size_t len;

        chunk_t msg = chunk_skip(in->get_data(in), 12);
        char *str = calloc(msg.len + 1, sizeof(char));
        memcpy(str, msg.ptr, msg.len);
        DBG1(DBG_IKE, "Get msg: %s\n", str);

        const char pass1[] = "testmsg";
        const char pass2[] = "10km";

        if(strcmp(str, "more") == 0) {
                len = sizeof(eap_20893_66666_header_t) + strlen(pass2);
                this->identifier = in->get_identifier(in);
                res = alloca(len);
                res->length = htons(len);
                res->code = EAP_RESPONSE;
                res->identifier = this->identifier;
                SETTYPEPLUSID(&res->type);
                res->vendor_type = htonl(VENDOR_TYPE);
                memcpy(res->data, pass2, strlen(pass2));

                *out = eap_payload_create_data(chunk_create((void*)res, len));
        }
        else {
                len = sizeof(eap_20893_66666_header_t) + strlen(pass1);
                this->identifier = in->get_identifier(in);
                res = alloca(len);
                res->length = htons(len);
                res->code = EAP_RESPONSE;
                res->identifier = this->identifier;
                SETTYPEPLUSID(&res->type);
                res->vendor_type = htonl(VENDOR_TYPE);
                memcpy(res->data, pass1, strlen(pass1));

                *out = eap_payload_create_data(chunk_create((void*)res, len));
        }

        free(str);

	return NEED_MORE;
}


METHOD(eap_method_t, process_server, status_t,
	private_eap_20893_66666_t *this, eap_payload_t *in, eap_payload_t **out)
{
	const char magic[] = "10km";

	chunk_t msg = chunk_skip(in->get_data(in), 12);
	char *str = calloc(msg.len + 1, sizeof(char));
	memcpy(str, msg.ptr, msg.len);
	DBG1(DBG_IKE, "Get msg: %s\n", str);

	if(strcmp(str, magic) == 0) {
		free(str);
		return SUCCESS;
	}
	else {
		eap_20893_66666_header_t *req;
		size_t len;
		const char more[] = "more";

		len = sizeof(eap_20893_66666_header_t) + strlen(more);
		req = alloca(len);
		req->length = htons(len);
		req->code = EAP_REQUEST;
		req->identifier = this->identifier;
		SETTYPEPLUSID(&req->type);
		req->vendor_type = htonl(VENDOR_TYPE);
		memcpy(req->data, more, strlen(more));

		*out = eap_payload_create_data(chunk_create((void*)req, len));

		free(str);
		return NEED_MORE;
	}
}

METHOD(eap_method_t, get_type, eap_type_t,
	private_eap_20893_66666_t *this, uint32_t *vendor)
{
	*vendor = VENDOR_ID;
	return VENDOR_TYPE;
}

METHOD(eap_method_t, get_msk, status_t,
	private_eap_20893_66666_t *this, chunk_t *msk)
{
	return FAILED;
}

METHOD(eap_method_t, get_identifier, uint8_t,
	private_eap_20893_66666_t *this)
{
	return this->identifier;
}

METHOD(eap_method_t, set_identifier, void,
	private_eap_20893_66666_t *this, uint8_t identifier)
{
	this->identifier = identifier;
}

METHOD(eap_method_t, is_mutual, bool,
	private_eap_20893_66666_t *this)
{
	return FALSE;
}

METHOD(eap_method_t, destroy, void,
	private_eap_20893_66666_t *this)
{
	this->peer->destroy(this->peer);
	this->server->destroy(this->server);
	free(this);
}

/**
 * Generic constructor
 */
static private_eap_20893_66666_t *eap_20893_66666_create_generic(identification_t *server,
												 identification_t *peer)
{
	private_eap_20893_66666_t *this;

	INIT(this,
		.public = {
			.eap_method_interface = {
				.get_type = _get_type,
				.is_mutual = _is_mutual,
				.get_msk = _get_msk,
				.get_identifier = _get_identifier,
				.set_identifier = _set_identifier,
				.destroy = _destroy,
			},
		},
		.peer = peer->clone(peer),
		.server = server->clone(server),
	);

	return this;
}

/*
 * see header
 */
eap_20893_66666_t *eap_20893_66666_create_server(identification_t *server, identification_t *peer)
{
	private_eap_20893_66666_t *this = eap_20893_66666_create_generic(server, peer);

	this->public.eap_method_interface.initiate = _initiate_server;
	this->public.eap_method_interface.process = _process_server;

	/* generate a non-zero identifier */
	do {
		this->identifier = random();
	} while (!this->identifier);

	return &this->public;
}

/*
 * see header
 */
eap_20893_66666_t *eap_20893_66666_create_peer(identification_t *server, identification_t *peer)
{
	private_eap_20893_66666_t *this = eap_20893_66666_create_generic(server, peer);

	this->public.eap_method_interface.initiate = _initiate_peer;
	this->public.eap_method_interface.process = _process_peer;

	return &this->public;
}
