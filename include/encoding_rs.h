
#ifndef cheddar_generated_encoding_rs_h
#define cheddar_generated_encoding_rs_h


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "encoding_rs_statics.h"

// Copyright 2015-2016 Mozilla Foundation. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// https://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or https://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

// THIS IS A GENERATED FILE. PLEASE DO NOT EDIT.
// Instead, please regenerate using encoding_c/build.rs.


/// Implements the
/// [_get an encoding_](https://encoding.spec.whatwg.org/#concept-encoding-get)
/// algorithm.
///
/// If, after ASCII-lowercasing and removing leading and trailing
/// whitespace, the argument matches a label defined in the Encoding
/// Standard, `const Encoding*` representing the corresponding
/// encoding is returned. If there is no match, `NULL` is returned.
///
/// The argument buffer can be in any ASCII-compatible encoding. It is not
/// required to be UTF-8.
///
/// # Undefined behavior
///
/// UB ensues if `label` and `label_len` don't designate a valid memory block.
Encoding const* encoding_for_label(uint8_t const* label, size_t label_len);

/// This function behaves the same as `encoding_for_label()`, except when
/// `encoding_for_label()` would return `REPLACEMENT_ENCODING`, this method
/// returns `NULL` instead.
///
/// This method is useful in scenarios where a fatal error is required
/// upon invalid label, because in those cases the caller typically wishes
/// to treat the labels that map to the replacement encoding as fatal
/// errors, too.
///
/// # Undefined behavior
///
/// UB ensues if `label` and `label_len` don't designate a valid memory block.
Encoding const* encoding_for_label_no_replacement(uint8_t const* label, size_t label_len);

/// Performs non-incremental BOM sniffing.
///
/// The argument must either be a buffer representing the entire input
/// stream (non-streaming case) or a buffer representing at least the first
/// three bytes of the input stream (streaming case).
///
/// Returns `UTF_8_ENCODING`, `UTF_16LE_ENCODING` or `UTF_16BE_ENCODING` if the
/// argument starts with the UTF-8, UTF-16LE or UTF-16BE BOM or `NULL`
/// otherwise. Upon return, `*buffer_len` is the length of the BOM (zero if
/// there is no BOM).
///
/// # Undefined behavior
///
/// UB ensues if `buffer` and `buffer_len` don't designate a valid memory block.
Encoding const* encoding_for_bom(uint8_t const* buffer, size_t* buffer_len);

/// If the argument matches exactly (case-sensitively; no whitespace
/// removal performed) the name of an encoding, returns
/// `const Encoding*` representing that encoding. Otherwise panics.
///
/// The motivating use case for this function is interoperability with
/// legacy Gecko code that represents encodings as name string instead of
/// type-safe `Encoding` objects. Using this function for other purposes is
/// most likely the wrong thing to do.
///
/// # Panics
///
/// Panics if the argument is not the name of an encoding.
///
/// # Undefined behavior
///
/// UB ensues if `name` and `name_len` don't designate a valid memory block.
Encoding const* encoding_for_name(uint8_t const* name, size_t name_len);

/// Writes the name of the given `Encoding` to a caller-supplied buffer as ASCII
/// and returns the number of bytes / ASCII characters written.
///
/// The output is not null-terminated.
///
/// The caller _MUST_ ensure that `name_out` points to a buffer whose length
/// is at least `ENCODING_NAME_MAX_LENGTH` bytes.
///
/// # Undefined behavior
///
/// UB ensues if either argument is `NULL` or if `name_out` doesn't point to
/// a valid block of memory whose length is at least `ENCODING_NAME_MAX_LENGTH`
/// bytes.
size_t encoding_name(Encoding const* encoding, uint8_t* name_out);

/// Checks whether the _output encoding_ of this encoding can encode every
/// Unicode scalar. (Only true if the output encoding is UTF-8.)
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
bool encoding_can_encode_everything(Encoding const* encoding);

/// Checks whether the bytes 0x00...0x7F map exclusively to the characters
/// U+0000...U+007F and vice versa.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
bool encoding_is_ascii_compatible(Encoding const* encoding);

/// Returns the _output encoding_ of this encoding. This is UTF-8 for
/// UTF-16BE, UTF-16LE and replacement and the encoding itself otherwise.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
Encoding const* encoding_output_encoding(Encoding const* encoding);

/// Allocates a new `Decoder` for the given `Encoding` on the heap with BOM
/// sniffing enabled and returns a pointer to the newly-allocated `Decoder`.
///
/// BOM sniffing may cause the returned decoder to morph into a decoder
/// for UTF-8, UTF-16LE or UTF-16BE instead of this encoding.
///
/// Once the allocated `Decoder` is no longer needed, the caller _MUST_
/// deallocate it by passing the pointer returned by this function to
/// `decoder_free()`.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
Decoder* encoding_new_decoder(Encoding const* encoding);

/// Allocates a new `Decoder` for the given `Encoding` on the heap with BOM
/// removal and returns a pointer to the newly-allocated `Decoder`.
///
/// If the input starts with bytes that are the BOM for this encoding,
/// those bytes are removed. However, the decoder never morphs into a
/// decoder for another encoding: A BOM for another encoding is treated as
/// (potentially malformed) input to the decoding algorithm for this
/// encoding.
///
/// Once the allocated `Decoder` is no longer needed, the caller _MUST_
/// deallocate it by passing the pointer returned by this function to
/// `decoder_free()`.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
Decoder* encoding_new_decoder_with_bom_removal(Encoding const* encoding);

/// Allocates a new `Decoder` for the given `Encoding` on the heap with BOM
/// handling disabled and returns a pointer to the newly-allocated `Decoder`.
///
/// If the input starts with bytes that look like a BOM, those bytes are
/// not treated as a BOM. (Hence, the decoder never morphs into a decoder
/// for another encoding.)
///
/// _Note:_ If the caller has performed BOM sniffing on its own but has not
/// removed the BOM, the caller should use
/// `encoding_new_decoder_with_bom_removal()` instead of this function to cause
/// the BOM to be removed.
///
/// Once the allocated `Decoder` is no longer needed, the caller _MUST_
/// deallocate it by passing the pointer returned by this function to
/// `decoder_free()`.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
Decoder* encoding_new_decoder_without_bom_handling(Encoding const* encoding);

/// Allocates a new `Decoder` for the given `Encoding` into memory provided by
/// the caller with BOM sniffing enabled. (In practice, the target should
/// likely be a pointer previously returned by `encoding_new_decoder()`.)
///
/// Note: If the caller has already performed BOM sniffing but has
/// not removed the BOM, the caller should still use this function in
/// order to cause the BOM to be ignored.
///
/// # Undefined behavior
///
/// UB ensues if either argument is `NULL`.
void encoding_new_decoder_into(Encoding const* encoding, Decoder* decoder);

/// Allocates a new `Decoder` for the given `Encoding` into memory provided by
/// the caller with BOM removal.
///
/// If the input starts with bytes that are the BOM for this encoding,
/// those bytes are removed. However, the decoder never morphs into a
/// decoder for another encoding: A BOM for another encoding is treated as
/// (potentially malformed) input to the decoding algorithm for this
/// encoding.
///
/// Once the allocated `Decoder` is no longer needed, the caller _MUST_
/// deallocate it by passing the pointer returned by this function to
/// `decoder_free()`.
///
/// # Undefined behavior
///
/// UB ensues if either argument is `NULL`.
void encoding_new_decoder_with_bom_removal_into(Encoding const* encoding, Decoder* decoder);

/// Allocates a new `Decoder` for the given `Encoding` into memory provided by
/// the caller with BOM handling disabled.
///
/// If the input starts with bytes that look like a BOM, those bytes are
/// not treated as a BOM. (Hence, the decoder never morphs into a decoder
/// for another encoding.)
///
/// _Note:_ If the caller has performed BOM sniffing on its own but has not
/// removed the BOM, the caller should use
/// `encoding_new_decoder_with_bom_removal_into()` instead of this function to
/// cause the BOM to be removed.
///
/// # Undefined behavior
///
/// UB ensues if either argument is `NULL`.
void encoding_new_decoder_without_bom_handling_into(Encoding const* encoding, Decoder* decoder);

/// Allocates a new `Encoder` for the given `Encoding` on the heap and returns a
/// pointer to the newly-allocated `Encoder`. (Exception, if the `Encoding` is
/// `replacement`, a new `Decoder` for UTF-8 is instantiated (and that
/// `Decoder` reports `UTF_8` as its `Encoding`).
///
/// Once the allocated `Encoder` is no longer needed, the caller _MUST_
/// deallocate it by passing the pointer returned by this function to
/// `encoder_free()`.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
Encoder* encoding_new_encoder(Encoding const* encoding);

/// Allocates a new `Encoder` for the given `Encoding` into memory provided by
/// the caller. (In practice, the target should likely be a pointer previously
/// returned by `encoding_new_encoder()`.)
///
/// # Undefined behavior
///
/// UB ensues if either argument is `NULL`.
void encoding_new_encoder_into(Encoding const* encoding, Encoder* encoder);

/// Validates UTF-8.
///
/// Returns the index of the first byte that makes the input malformed as
/// UTF-8 or `buffer_len` if `buffer` is entirely valid.
///
/// # Undefined behavior
///
/// UB ensues if `buffer` and `buffer_len` don't designate a valid memory block.
size_t encoding_utf8_valid_up_to(uint8_t const* buffer, size_t buffer_len);

/// Validates ASCII.
///
/// Returns the index of the first byte that makes the input malformed as
/// ASCII or `buffer_len` if `buffer` is entirely valid.
///
/// # Undefined behavior
///
/// UB ensues if `buffer` and `buffer_len` don't designate a valid memory block.
size_t encoding_ascii_valid_up_to(uint8_t const* buffer, size_t buffer_len);

/// Validates ISO-2022-JP ASCII-state data.
///
/// Returns the index of the first byte that makes the input not representable
/// in the ASCII state of ISO-2022-JP or `buffer_len` if `buffer` is entirely
/// representable in the ASCII state of ISO-2022-JP.
///
/// # Undefined behavior
///
/// UB ensues if `buffer` and `buffer_len` don't designate a valid memory block.
size_t encoding_iso_2022_jp_ascii_valid_up_to(uint8_t const* buffer, size_t buffer_len);

/// Deallocates a `Decoder` previously allocated by `encoding_new_decoder()`.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
void decoder_free(Decoder* decoder);

/// The `Encoding` this `Decoder` is for.
///
/// BOM sniffing can change the return value of this method during the life
/// of the decoder.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
Encoding const* decoder_encoding(Decoder const* decoder);

/// Query the worst-case UTF-8 output size _with replacement_.
///
/// Returns the size of the output buffer in UTF-8 code units (`uint8_t`)
/// that will not overflow given the current state of the decoder and
/// `byte_length` number of additional input bytes when decoding with
/// errors handled by outputting a REPLACEMENT CHARACTER for each malformed
/// sequence.
///
/// # Undefined behavior
///
/// UB ensues if `decoder` is `NULL`.
size_t decoder_max_utf8_buffer_length(Decoder const* decoder, size_t byte_length);

/// Query the worst-case UTF-8 output size _without replacement_.
///
/// Returns the size of the output buffer in UTF-8 code units (`uint8_t`)
/// that will not overflow given the current state of the decoder and
/// `byte_length` number of additional input bytes when decoding without
/// replacement error handling.
///
/// Note that this value may be too small for the `_with_replacement` case.
/// Use `decoder_max_utf8_buffer_length()` for that case.
///
/// # Undefined behavior
///
/// UB ensues if `decoder` is `NULL`.
size_t decoder_max_utf8_buffer_length_without_replacement(Decoder const* decoder, size_t byte_length);

/// Incrementally decode a byte stream into UTF-8 with malformed sequences
/// replaced with the REPLACEMENT CHARACTER.
///
/// See the top-level FFI documentation for documentation for how the
/// `decoder_decode_*` functions are mapped from Rust and the documentation
/// for the [`Decoder`][1] struct for the semantics.
///
/// # Undefined behavior
///
/// UB ensues if `decoder` is `NULL`, `src` and `src_len` don't designate a
/// valid block of memory, `dst` and `dst_len` don't designate a valid block
/// of memory or `had_replacements` is `NULL`.
///
/// [1]: ../struct.Decoder.html
uint32_t decoder_decode_to_utf8(Decoder* decoder, uint8_t const* src, size_t* src_len, uint8_t* dst, size_t* dst_len, bool last, bool* had_replacements);

/// Incrementally decode a byte stream into UTF-8 _without replacement_.
///
/// See the top-level FFI documentation for documentation for how the
/// `decoder_decode_*` functions are mapped from Rust and the documentation
/// for the [`Decoder`][1] struct for the semantics.
///
/// # Undefined behavior
///
/// UB ensues if `decoder` is `NULL`, `src` and `src_len` don't designate a
/// valid block of memory or `dst` and `dst_len` don't designate a valid block
/// of memory.
///
/// [1]: ../struct.Decoder.html
uint32_t decoder_decode_to_utf8_without_replacement(Decoder* decoder, uint8_t const* src, size_t* src_len, uint8_t* dst, size_t* dst_len, bool last);

/// Query the worst-case UTF-16 output size (with or without replacement).
///
/// Returns the size of the output buffer in UTF-16 code units (`char16_t`)
/// that will not overflow given the current state of the decoder and
/// `byte_length` number of additional input bytes.
///
/// Since the REPLACEMENT CHARACTER fits into one UTF-16 code unit, the
/// return value of this method applies also in the
/// `_without_replacement` case.
///
/// # Undefined behavior
///
/// UB ensues if `decoder` is `NULL`.
size_t decoder_max_utf16_buffer_length(Decoder const* decoder, size_t u16_length);

/// Incrementally decode a byte stream into UTF-16 with malformed sequences
/// replaced with the REPLACEMENT CHARACTER.
///
/// See the top-level FFI documentation for documentation for how the
/// `decoder_decode_*` functions are mapped from Rust and the documentation
/// for the [`Decoder`][1] struct for the semantics.
///
/// # Undefined behavior
///
/// UB ensues if `decoder` is `NULL`, `src` and `src_len` don't designate a
/// valid block of memory, `dst` and `dst_len` don't designate a valid block
/// of memory or `had_replacements` is `NULL`.
///
/// [1]: ../struct.Decoder.html
uint32_t decoder_decode_to_utf16(Decoder* decoder, uint8_t const* src, size_t* src_len, char16_t* dst, size_t* dst_len, bool last, bool* had_replacements);

/// Incrementally decode a byte stream into UTF-16 _without replacement_.
///
/// See the top-level FFI documentation for documentation for how the
/// `decoder_decode_*` functions are mapped from Rust and the documentation
/// for the [`Decoder`][1] struct for the semantics.
///
/// # Undefined behavior
///
/// UB ensues if `decoder` is `NULL`, `src` and `src_len` don't designate a
/// valid block of memory or `dst` and `dst_len` don't designate a valid block
/// of memory.
///
/// [1]: ../struct.Decoder.html
uint32_t decoder_decode_to_utf16_without_replacement(Decoder* decoder, uint8_t const* src, size_t* src_len, char16_t* dst, size_t* dst_len, bool last);

/// Deallocates an `Encoder` previously allocated by `encoding_new_encoder()`.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
void encoder_free(Encoder* encoder);

/// The `Encoding` this `Encoder` is for.
///
/// # Undefined behavior
///
/// UB ensues if the argument is `NULL`.
Encoding const* encoder_encoding(Encoder const* encoder);

/// Query the worst-case output size when encoding from UTF-8 with
/// replacement.
///
/// Returns the size of the output buffer in bytes that will not overflow
/// given the current state of the encoder and `byte_length` number of
/// additional input code units if there are no unmappable characters in
/// the input.
size_t encoder_max_buffer_length_from_utf8_if_no_unmappables(Encoder const* encoder, size_t byte_length);

/// Query the worst-case output size when encoding from UTF-8 without
/// replacement.
///
/// Returns the size of the output buffer in bytes that will not overflow
/// given the current state of the encoder and `byte_length` number of
/// additional input code units.
size_t encoder_max_buffer_length_from_utf8_without_replacement(Encoder const* encoder, size_t byte_length);

/// Incrementally encode into byte stream from UTF-8 with unmappable
/// characters replaced with HTML (decimal) numeric character references.
///
/// The input absolutely _MUST_ be valid UTF-8 or the behavior is memory-unsafe!
/// If in doubt, check the validity of input before using!
///
/// See the top-level FFI documentation for documentation for how the
/// `encoder_encode_*` functions are mapped from Rust and the documentation
/// for the [`Encoder`][1] struct for the semantics.
///
/// UB ensues if `encoder` is `NULL`, `src` and `src_len` don't designate a
/// valid block of memory, `dst` and `dst_len` don't designate a valid block
/// of memory, `had_replacements` is `NULL` or the input is not valid UTF-8.
///
/// [1]: ../struct.Encoder.html
uint32_t encoder_encode_from_utf8(Encoder* encoder, uint8_t const* src, size_t* src_len, uint8_t* dst, size_t* dst_len, bool last, bool* had_replacements);

/// Incrementally encode into byte stream from UTF-8 _without replacement_.
///
/// See the top-level FFI documentation for documentation for how the
/// `encoder_encode_*` functions are mapped from Rust and the documentation
/// for the [`Encoder`][1] struct for the semantics.
///
/// The input absolutely _MUST_ be valid UTF-8 or the behavior is memory-unsafe!
/// If in doubt, check the validity of input before using!
///
/// # Undefined behavior
///
/// UB ensues if `encoder` is `NULL`, `src` and `src_len` don't designate a
/// valid block of memory, `dst` and `dst_len` don't designate a valid block
/// of memory or the input is not valid UTF-8.
///
/// [1]: ../struct.Encoder.html
uint32_t encoder_encode_from_utf8_without_replacement(Encoder* encoder, uint8_t const* src, size_t* src_len, uint8_t* dst, size_t* dst_len, bool last);

/// Query the worst-case output size when encoding from UTF-16 with
/// replacement.
///
/// Returns the size of the output buffer in bytes that will not overflow
/// given the current state of the encoder and `u16_length` number of
/// additional input code units if there are no unmappable characters in
/// the input.
size_t encoder_max_buffer_length_from_utf16_if_no_unmappables(Encoder const* encoder, size_t u16_length);

/// Query the worst-case output size when encoding from UTF-16 without
/// replacement.
///
/// Returns the size of the output buffer in bytes that will not overflow
/// given the current state of the encoder and `u16_length` number of
/// additional input code units.
size_t encoder_max_buffer_length_from_utf16_without_replacement(Encoder const* encoder, size_t u16_length);

/// Incrementally encode into byte stream from UTF-16 with unmappable
/// characters replaced with HTML (decimal) numeric character references.
///
/// See the top-level FFI documentation for documentation for how the
/// `encoder_encode_*` functions are mapped from Rust and the documentation
/// for the [`Encoder`][1] struct for the semantics.
///
/// UB ensues if `encoder` is `NULL`, `src` and `src_len` don't designate a
/// valid block of memory, `dst` and `dst_len` don't designate a valid block
/// of memory or `had_replacements` is `NULL`.
///
/// [1]: ../struct.Encoder.html
uint32_t encoder_encode_from_utf16(Encoder* encoder, char16_t const* src, size_t* src_len, uint8_t* dst, size_t* dst_len, bool last, bool* had_replacements);

/// Incrementally encode into byte stream from UTF-16 _without replacement_.
///
/// See the top-level FFI documentation for documentation for how the
/// `encoder_encode_*` functions are mapped from Rust and the documentation
/// for the [`Encoder`][1] struct for the semantics.
///
/// # Undefined behavior
///
/// UB ensues if `encoder` is `NULL`, `src` and `src_len` don't designate a
/// valid block of memory or `dst` and `dst_len` don't designate a valid block
/// of memory.
///
/// [1]: ../struct.Encoder.html
uint32_t encoder_encode_from_utf16_without_replacement(Encoder* encoder, char16_t const* src, size_t* src_len, uint8_t* dst, size_t* dst_len, bool last);



#ifdef __cplusplus
}
#endif


#endif
