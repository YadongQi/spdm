/**
    Copyright Notice:
    Copyright 2021 DMTF. All rights reserved.
    License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
**/

#ifndef __SPDM_SECURED_MESSAGE_LIB_INTERNAL_H__
#define __SPDM_SECURED_MESSAGE_LIB_INTERNAL_H__

#include <library/spdm_secured_message_lib.h>

typedef struct {
	uint8_t dhe_secret[MAX_DHE_KEY_SIZE];
	uint8_t handshake_secret[MAX_HASH_SIZE];
	uint8_t master_secret[MAX_HASH_SIZE];
} spdm_session_info_struct_master_secret_t;

typedef struct {
	uint8_t request_handshake_secret[MAX_HASH_SIZE];
	uint8_t response_handshake_secret[MAX_HASH_SIZE];
	uint8_t export_master_secret[MAX_HASH_SIZE];
	uint8_t request_finished_key[MAX_HASH_SIZE];
	uint8_t response_finished_key[MAX_HASH_SIZE];
	uint8_t request_handshake_encryption_key[MAX_AEAD_KEY_SIZE];
	uint8_t request_handshake_salt[MAX_AEAD_IV_SIZE];
	uint64_t request_handshake_sequence_number;
	uint8_t response_handshake_encryption_key[MAX_AEAD_KEY_SIZE];
	uint8_t response_handshake_salt[MAX_AEAD_IV_SIZE];
	uint64_t response_handshake_sequence_number;
} spdm_session_info_struct_handshake_secret_t;

typedef struct {
	uint8_t request_data_secret[MAX_HASH_SIZE];
	uint8_t response_data_secret[MAX_HASH_SIZE];
	uint8_t request_data_encryption_key[MAX_AEAD_KEY_SIZE];
	uint8_t request_data_salt[MAX_AEAD_IV_SIZE];
	uint64_t request_data_sequence_number;
	uint8_t response_data_encryption_key[MAX_AEAD_KEY_SIZE];
	uint8_t response_data_salt[MAX_AEAD_IV_SIZE];
	uint64_t response_data_sequence_number;
} spdm_session_info_struct_application_secret_t;

typedef struct {
	spdm_session_type_t session_type;
	spdm_version_number_t version;
	spdm_version_number_t secured_message_version;
	uint32_t base_hash_algo;
	uint16_t dhe_named_group;
	uint16_t aead_cipher_suite;
	uint16_t key_schedule;
	uintn hash_size;
	uintn dhe_key_size;
	uintn aead_key_size;
	uintn aead_iv_size;
	uintn aead_tag_size;
	boolean use_psk;
	boolean finished_key_ready;
	spdm_session_state_t session_state;
	spdm_session_info_struct_master_secret_t master_secret;
	spdm_session_info_struct_handshake_secret_t handshake_secret;
	spdm_session_info_struct_application_secret_t application_secret;
	spdm_session_info_struct_application_secret_t application_secret_backup;
	boolean requester_backup_valid;
	boolean responder_backup_valid;
	uintn psk_hint_size;
	void *psk_hint;
	//
	// Cache the error in spdm_decode_secured_message. It is handled in libspdm_build_response.
	//
	spdm_error_struct_t last_spdm_error;
} spdm_secured_message_context_t;

#endif