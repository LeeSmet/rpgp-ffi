#include <stdio.h>
#include <string.h>
#include "librpgp.h"

int main() {
	const char *user = "sometestuser";
	// Generate a new x25519 secret key
	rpgp_signed_secret_key *sk = rpgp_create_x25519_skey(user);
	// Get the public key
	rpgp_signed_public_key *pk = rpgp_skey_public_key(sk);
	// Get key id
	char *key_id = rpgp_skey_key_id(sk); 
	printf("key id: %s\n\n", key_id);
	// Cleanup
	rpgp_string_drop(key_id);
	rpgp_key_drop((rpgp_public_or_secret_key *)pk);
	rpgp_key_drop((rpgp_public_or_secret_key *)sk);

	// Generate a message
	char *fake_file_name = "some_file_to_send";
	char *msg_content = "this is a very secret message\n";

	rpgp_message *msg = rpgp_msg_new_raw(fake_file_name,(const uint8_t *)msg_content, strlen(msg_content));
	int err_len = rpgp_last_error_length();
	if (err_len != 0) {
		char *last_err = rpgp_last_error_message();
		printf("%s\n", last_err);
		rpgp_string_drop(last_err);
		return 1;
	}


	// Armor the message
	char *armored_msg = rpgp_msg_to_armored_str(msg);
	rpgp_msg_drop(msg);
	printf("%s\n", armored_msg);
	// Remove msg armor
	rpgp_message *original_msg = rpgp_msg_from_armor(armored_msg, strlen(armored_msg));
	if (err_len != 0) {
		char *last_err = rpgp_last_error_message();
		printf("%s\n\n", last_err);
		rpgp_string_drop(last_err);
		return 1;
	}
	rpgp_string_drop(armored_msg);

	// verify
	char *content = rpgp_msg_to_str(original_msg);
	rpgp_msg_drop(original_msg);
	printf("%s", content);
	rpgp_string_drop(content);

	return 0;
}
