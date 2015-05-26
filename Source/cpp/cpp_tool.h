#ifndef XEEN_CPP_TOOL_H
#define XEEN_CPP_TOOL_H

/** @file cpp_tool.c
 *
 *  Interface to the copy-protection file type.
 *
 *  A copy-protection file contains a sequence of copy-protection entries. Each
 *  entry consists of the page, the line and to word to look up, all stored as
 *  single bytes.  The remaining 13 bytes are the answer string the game
 *  expects from the player.
 *
 *  +--------+-----------+-------------------------+
 *  | Name   | Type      | Description             |
 *  +========+===========+=========================+
 *  | page   | uint8     | Page number to look up. |
 *  +--------+-----------+-------------------------+
 *  | line   | uint8     | Line number to look up. |
 *  +--------+-----------+-------------------------+
 *  | word   | uint8     | Word number to look up. |
 *  +--------+-----------+-------------------------+
 *  | string | uint8[13] | String to expect.       |
 *  +--------+-----------+-------------------------+
 *
 *  The string is null-terminated and right-padded with null if necessary. The
 *  first three members are used to generate the question for the player, the
 *  string is used to verify the player's answer.
 */
#include <stdint.h>
#include <stdio.h>

/** Length of the copy-protection string. */
#define XEEN_CPP_LENGTH  13

/** Structure of a copy-protection question. */
typedef struct xeen_copy_protection {
	uint8_t page; /**< Page number to look up. */
	uint8_t line; /**< Line number to look up. */
	uint8_t word; /**< Word number to look up. */

	/** String to compare user input to. */
	uint8_t string[XEEN_CPP_LENGTH];
}XeenCopyProtection;

/** Read a copy-protection entry from file.
 *
 *  @param fp     File pointer
 *  @param o      Offset to the copy protection data.
 *  @param index  Index of the copy-protection entry.
 *  @param prot   Pointer to store the result in.
 *
 *  @return Error code:
 *            - 0: Success
 *            - 1: Invalid arguments
 *            - 2: Failed reading file.
 *            - 3: Invalid/corrupted data.
 *
 *  @pre  The pointers must be valid.
 *  @pre  The data to `*prot` must be invalid (i.e. all 0) and the first
 *        character of the string is `'\0'`.
 *
 *  @post  The variable `*prot` will contain the read data on success.
 *  @post  The last character of `*prot.string` will be `'\0'`.
 */
int xeen_read_copy_protection(FILE *fp, long o, int index, XeenCopyProtection *prot);

#endif /* XEEN_CPP_TOOL_H */

