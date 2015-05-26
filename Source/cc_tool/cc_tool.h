#ifndef XEEN_CC_TOOL_H
#define XEEN_CC_TOOL_H

/** @file cc_tool.h
 *
 *  CC file extraction library.
 *
 *  This interface provides capabilities for extracting content from CC file
 *  archives. A CC file consists of the file count, a table of contents (TOC)
 *  and the sequence of files. In some cases the files are encrypted with a
 *  very simple algorithm, but they are never compressed (except for *Might &
 *  Magic III*, which is not supported).
 *
 *  +------------------+-------+--------------------------------+
 *  | Type             | Name  | Description                    |
 *  +==================+=======+================================+
 *  | uint16           | count | Number of files in the CC file |
 *  +------------------+-------+--------------------------------+
 *  | uint8[8 * count] | toc   | Table of contents              |
 *  +------------------+-------+--------------------------------+
 *  | uint8[]          | files | Sequence of files              |
 *  +------------------+-------+--------------------------------+
 *
 *  All multi-byte integers are stored in the file in little-endian notation.
 *
 *  It is important to note that the structure that describes a TOC entry in
 *  this library is not the same as the one used by the game. A TOC entry in
 *  the CC file has the following structure:
 *
 *  +--------+---------+-----------------------+
 *  | Type   | Name    | Description           |
 *  +========+=========+=======================+
 *  | uint16 | ID      | Hashed file name      |
 *  +--------+---------+-----------------------+
 *  | uint32 | offset  | Offset in the CC file |
 *  +--------+---------+-----------------------+
 *  | uint16 | length  | Length of the file    |
 *  +--------+---------+-----------------------+
 *  | uint8  | padding | Must be 0, no used    |
 *  +--------+---------+-----------------------+
 *
 *  Since there is no `uint24_t` type in C I have decided to use a `uint32_t`
 *  variable instead and omit the padding byte.
 *
 *  The file name is not stored, instead it is hashed into an ID number, a
 *  function can be used to hash a string. That way if you know the name of the
 *  file you can identify it by its ID number.
 *
 *  Retrieving a file is not covered in this library because that would be
 *  too-specific, instead it provides all features necessary to get from a file
 *  name to the raw bytes. The steps are:
 *
 *    1. Hash the file name to get the ID
 *    2. Get the number of files to limit the number of search attempts.
 *    3. Search through the TOC for an entry with that ID.
 *    4. If the entry has been found jump to that offset.
 *    5. Read and if necessary XOR the bytes.
 *
 *  Some CC files store their files as they are, but other store every byte
 *  encrypted. To decrypt them every byte must be XORed with the value of
 *  `XEEN_CC_XOR_VAL`. There is no way of automatically telling which CC files
 *  used encryption and which ones don't, but if it does, then every contained
 *  file is encrypted. As a rule, saved-game CC files like DARK01.SAV,
 *  XEEN01.SAV, etc. are *not* XORed, while all others (XEEN.CC, DARK.CC,
 *  INTRO.CC, SWRD.CC) *are* XORed.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/** If a file is encrypted every byte must be XORed with this value. */
#define XEEN_CC_XOR_VAL  0x35

/** Structure of a CC file TOC entry.
 *
 *  Only the first three bytes of the offset are used, so the variable is one
 *  byte larger than what the game uses. In return the padding byte at the end
 *  used by the game is not needed.
 */
typedef struct cc_toc_entry {
	uint16_t file_id;      /**< File ID inside the CC file.   */
	uint32_t file_offset;  /**< Offset of the in the CC file. */
	uint16_t file_length;  /**< Length of the file.           */
} XeenCCTocEntry;

/** Hash a file name to a file ID.
 *
 *  @param hash  Pointer to variable to hold the hash.
 *  @param name  NUL-terminated string of the file name.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments (see precondition)
 *
 *  @pre The hash must be a valid pointer.
 *  @pre The file name must not be empty.
 *  @pre The file name must only contain ASCII characters.
 *  @pre The file name must be no longer than 12 characters (eight characters
 *       for the name, one period and three for the extension), these are the
 *       DOS rules.
 *
 *  If the function is not successful the contents of the hash variable are not
 *  altered. This function is case-insensitive.
 */
int xeen_hash_filename(uint16_t *hash, char *name);

/** Get the number of files stored in the CC file.
 *
 *  @param fp     File pointer to open CC file.
 *  @param count  Pointer to the variable to store the count in.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments (see preconditions)
 *             - 2: File seek fail
 *             - 3: File read fail
 *
 *  @pre The pointer arguments must all be valid.
 *
 *  @post If the function was successful the `count` variable points to the
 *        result
 */
int xeen_cc_file_count(FILE *fp, uint16_t *count);

/** Get the decrypted TOC entry stored in a CC file.
 *
 *  @param fp     File pointer to open CC file.
 *  @param index  Index of the TOC entry in the TOC.
 *  @param entry  Pointer to a variable to store the result in.
 *
 *  @return  Error code:
 *             - 0: Success
 *             - 1: Invalid arguments (see preconditions)
 *             - 2: File seek fail
 *             - 3: File read fail
 *
 *  @pre The pointer variables must be valid.
 *
 *  @post If the function was successful the `entry` variable points to the
 *        result.
 *
 *  The function does not check whether the index is within legal bounds, so
 *  the caller should get the file count of the CC file first.
 */
int xeen_cc_get_toc_entry(FILE *fp, const int index, XeenCCTocEntry *entry);

#endif /* XEEN_CC_TOOL_H */

