#ifndef CANIM_SHARED_H
#define CANIM_SHARED_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define CANIM_API __attribute__((visibility("default")))
typedef uint32_t CanimResult;

// status code helpers
#define STATUS_TYPE_SHIFT 24
#define STATUS_TYPE_MASK 0xFF000000
#define STATUS_INFO_MASK 0x00FFFFFF

/// @brief Operation succeeded.
#define SUCCESS 0x00

/// @brief No operation performed.
#define NOOP 0x01

/// @brief Non-fatal error.
#define NONFATAL 0x02

/// @brief Fatal error.
#define FATAL 0x03

/// @brief Extracts the status type (SUCCESS/NOOP/NONFATAL/FATAL).
#define STATUS_TYPE(code) (((code) & STATUS_TYPE_MASK) >> STATUS_TYPE_SHIFT)

/// @brief True if code is an error (NONFATAL or FATAL).
#define IS_AN_ERROR(x)                                                         \
  ((STATUS_TYPE((x)) == FATAL) || (STATUS_TYPE((x)) == NONFATAL))

// Error codes
#define TRI_INIT_MALLOC_FAIL 0x03000000 ///< Triangulation malloc failed.
#define TRI_NOT_FOUND 0x03000001        ///< Triangulation pointer was NULL.
#define ADDING_TRI_REALLOC_FAILURE                                             \
  0x03000002 ///< Realloc failed while adding triangle.
#define PSLG_INIT_MALLOC_ERROR 0x03000003   ///< PSLG struct allocation failed.
#define PSLG_VERTEX_MALLOC_ERROR 0x03000004 ///< Vertex allocation failed.
#define PSLG_EDGE_MALLOC_ERROR 0x03000005   ///< Edge allocation failed.
#define PSLG_EDGE_SPLIT_VERTEX_REALLOC_ERROR                                   \
  0x03000006 ///< Realloc failed in split (vertices).
#define PSLG_EDGE_SPLIT_EDGE_REALLOC_ERROR                                     \
  0x03000007 ///< Realloc failed in split (edges).
#define PSLG_TRIANGULATION_INIT_MALLOC_ERROR                                   \
  0x03000008 ///< Coupled PSLG+tri malloc failed.
#define PSLG_ATTACK_TEMP_EDGES_MALLOC_ERROR                                    \
  0x03000009 ///< Attack: malloc for temp edges failed.
#define PSLG_ATTACK_EDGE_REALLOCATION_ERROR                                    \
  0x0300000a ///< Attack: realloc failed on edges.
#define TRIANGULATE_POLYHEDRON_BATCH_TRIANGULATIONS_MALLOC_ERROR               \
  0x0300000b ///< Allocating an array of triangulation pointers failed when
             ///< triangulation a polyhedron.
#define TRIANGULATE_POLYHEDRON_VERTEX_MALLOC_ERROR                             \
  0x0300000c ///< When triangulating the polyhedron, allocating memory for
             ///< vertices failed
#define POLYHEDRON_MALLOC_ERROR                                                \
  0x0300000d ///< When allocating memory for polyhedron, malloc failed
#define POLYHEDRON_VERTEX_MALLOC_ERROR                                         \
  0x0300000e ///< When allocating memory for the vertices of a polyhedron,
             ///< malloc failed
#define POLYHEDRON_FACE_MALLOC_ERROR                                           \
  0x0300000f ///< When allocating memory for the faces of a polyhedron, malloc
             ///< failed
#define POLYHEDRON_FACE_SIZES_MALLOC_ERROR                                     \
  0x03000010 ///< When allocating memory for the face sizes of the polyhedron,
             ///< malloc failed
#define FILE_NO_CLEAN_LINE_OFF_ERROR                                           \
  0x03000011 ///< When reading an off file, it could not find a clean line
#define OFF_HEADER_OFF_ERROR                                                   \
  0x03000012 ///< When reading an off file the first part of the off header was
             ///< absent
#define OFF_HEADER_DATA_ERROR                                                  \
  0x03000013 ///< When reading an off file the second part of the off header was
             ///< absent
#define OFF_VERTEX_ERROR 0x03000014 ///< Reading a vertex of an off file failed
#define OFF_FACE_ERROR 0x03000015   ///< Reading a face of an off file failed
#define DEDUP_PSLG_VERTEX_REALLOC_ERROR                                        \
  0x03000016 ///< When deduplicating pslg vertices memory reallocation failed.
#define DEDUP_PSLG_EDGES_REALLOC_ERROR                                         \
  0x03000017 ///< When deduplicating pslg edges memory reallocation failed.
#define STL_HEADER_WRITE_ERROR                                                 \
  0x03000018 ///< When writing to header of stl, writing failed
#define STL_VECTOR_WRITE_ERROR                                                 \
  0x03000019 ///< When writing to vector of stl, writing failed
#define RGB_BUFFER_MALLOC_ERROR                                                \
  0x0300001a ///< When allocating a rgb buffer, malloc failed
#define LOAD_OPENGL_FUNCTION_ERROR                                             \
  0x0300001b ///< If an OPENGL function fails we are screwed
#define OPENGL_SHADER_COMPILATION_ERROR                                        \
  0x0300001c ///< When compiling a shader an error occured
#define OPENGL_SHADER_PROGRAM_LINK_ERROR                                       \
  0x0300001d ///< When linking a shader program an error occured
#define DRAW_TRIANGULATION_MALLOC_ERROR                                        \
  0x0300001e ///< When drawing a trianglulation, malloc failed
#define TRI_CLONE_ERROR                                                        \
  0x0300001f ///< Malloc failed when cloning a triangulation
#define TRI_CLONE_TRI_ERROR                                                    \
  0x03000020 ///< Malloc failed when cloning the triangles in a triangulation
#define PDF_XREF_FIND_SEEK_END_ERROR                                           \
  0x03000021 ///< When trying to find the xref table in a pdf, fseek failed to
             ///< seek to the end
#define PDF_XREF_FIND_FTELL_ERROR                                              \
  0x03000022 ///< When trying to find the xref table in a pdf, ftell failed
#define PDF_XREF_FIND_SEEK_SET_ERROR                                           \
  0x03000023 ///< When trying to find the xref table in a pdf, fseek failed to
             ///< set the seek
#define PDF_XREF_STARTXREF_NOT_FOUND                                           \
  0x03000024 ///< When trying to find the xref table in a pdf, the string
             ///< startxref was not found
#define PDF_XREF_OFFSET_PARSE_ERROR                                            \
  0x03000025 ///< When trying to find the xref table in the pdf the offset could
             ///< not be properly parsed.
#define PDF_XREF_FIND_FREAD_ERROR                                              \
  0x03000026 ///< When trying to find the xref table in a pdf, fread failed
#define NEXT_STR_NOT_FOUND_ERROR                                               \
  0x03000027 ///< When using next_str, the character "\0" was not found
#define GET_XREF_FSEEK_ERROR 0x03000028 ///< When getting the xref, fseek failed
#define GET_XREF_FREAD_ERROR                                                   \
  0x03000029 ///< When getting the xref, fread failed.
#define GET_XREF_STRCHR_NEWLINE_FAIL                                           \
  0x0300002a ///< When getting xref, strchr to look at new line failed.
#define NON_XREF_XREF 0x0300002b ///< The type of the xref table is not an xref
#define GET_XREF_STREAM_SEEK_ERROR                                             \
  0x0300002c ///< When getting the xref seeking the stream failed
#define STREAM_DECOMPRESS_MALLOC_FAIL                                          \
  0x0300002d ///< Allocating memory for decompressed stream failed
#define STREAM_DECOMPRESS_INIT_FAIL                                            \
  0x0300002e ///< Initializing the stream decompression failed
#define STREAM_DECOMPRESS_FAIL 0x0300002f ///< Decompressing streams failed
#define GET_XREF_STREAM_MALLOC_ERROR                                           \
  0x03000030 ///< When getting the xref allocating memory to store the stream
             ///< failed
#define GET_XREF_STREAM_READ_ERROR                                             \
  0x03000031 ///< Reading the file to store the xref stream failed
#define GET_XREF_MALLOC_ERROR                                                  \
  0x03000032 ///< When getting the xref, allocating the PDFXref object failed
#define GET_XREF_TABLE_ENTRIES_MALLOC_ERROR                                    \
  0x03000033 ///< When getting the xref table entries, malloc failed
#define GL_GFX_DEVICE_CALLOC_ERROR                                             \
  0x03000034 ///< When using calloc to allocate memory for OpenGL GfxDevice,
             ///< calloc failed
/**
 * @brief Print out the error
 * @param error The error the need be printed.
 * @return I will not return anything
 */

void print_error(CanimResult error) {
  if (!IS_AN_ERROR(error)) {
    return;
  }
  switch (error) {
  case TRI_INIT_MALLOC_FAIL:
    fprintf(stderr, "Allocating memory when initializing a triangle failed.\n");
    break;
  case TRI_NOT_FOUND:
    fprintf(stderr, "When running add_triangulation, you inputted a NULL "
                    "pointer which is very mean of you.\n");
    break;
  case ADDING_TRI_REALLOC_FAILURE:
    fprintf(stderr, "When adding a triangle to a triangulation (running "
                    "add_triangle) we failed at reallocating the memory.\n");
    break;
  case PSLG_INIT_MALLOC_ERROR:
    fprintf(stderr, "When mallocing the PSLG, I failed.\n");
    break;
  case PSLG_VERTEX_MALLOC_ERROR:
    fprintf(stderr, "Allocating the vertices for the PSLG failed.\n");
    break;
  case PSLG_EDGE_MALLOC_ERROR:
    fprintf(stderr, "Allocating the edges for the PSLG failed\n");
    break;
  case PSLG_EDGE_SPLIT_VERTEX_REALLOC_ERROR:
    fprintf(stderr, "When splitting a pslg at two edges, reallocating the "
                    "space for the vertices failed.\n");
    break;
  case PSLG_EDGE_SPLIT_EDGE_REALLOC_ERROR:
    fprintf(stderr, "When splitting a pslg at two edges, reallocating the "
                    "space for the edge failed.\n");
    break;
  case PSLG_TRIANGULATION_INIT_MALLOC_ERROR:
    fprintf(stderr, "When creating a pslg triangulation, allocating memory for "
                    "the pslg triangulation failed.\n");
    break;
  case PSLG_ATTACK_TEMP_EDGES_MALLOC_ERROR:
    fprintf(stderr, "When attacking a PSLG triangulation, using malloc to "
                    "allocate temporary edge list failed.\n");
    break;
  case PSLG_ATTACK_EDGE_REALLOCATION_ERROR:
    fprintf(stderr,
            "This shouldn't happen, but in the rare case it does, shrinking "
            "the memory during a PSLG vertex attack somehow failed.\n");
    break;
  case TRIANGULATE_POLYHEDRON_BATCH_TRIANGULATIONS_MALLOC_ERROR:
    fprintf(stderr, "When allocating a bunch an array of triangulation "
                    "pointers, Memory allocating failed\n");
    break;
  case TRIANGULATE_POLYHEDRON_VERTEX_MALLOC_ERROR:
    fprintf(stderr, "When allocating vertices during polyhedron triangulation, "
                    "malloc failed.\n");
    break;
  case POLYHEDRON_MALLOC_ERROR:
    fprintf(stderr, "When allocating a polyhedron, malloc failed\n");
    break;
  case POLYHEDRON_VERTEX_MALLOC_ERROR:
    fprintf(stderr,
            "When allocating the vertices of the polyhedron, malloc failed\n");
    break;
  case POLYHEDRON_FACE_MALLOC_ERROR:
    fprintf(stderr,
            "When allocating the faces of the polyhedron, malloc failed\n");
    break;
  case POLYHEDRON_FACE_SIZES_MALLOC_ERROR:
    fprintf(
        stderr,
        "When allocating the face sizes of the polyhedron, malloc failed\n");
    break;
  case FILE_NO_CLEAN_LINE_OFF_ERROR:
    fprintf(stderr, "When reading an off file and trying to find a clean line, "
                    "there was non.\n");
    break;
  case OFF_HEADER_OFF_ERROR:
    fprintf(stderr, "When reading and OFF file the \"OFF\" part of the header "
                    "was excluded\n");
    break;
  case OFF_HEADER_DATA_ERROR:
    fprintf(stderr, "When reading the actaul data of an off file header, (so "
                    "vertex count and edge count) it was missing. \n");
    break;
  case OFF_VERTEX_ERROR:
    fprintf(stderr,
            "When reading a vertex from an off file something went wrong\n");
    break;
  case OFF_FACE_ERROR:
    fprintf(stderr,
            "When reading a face from an off file something went wrong\n");
    break;
  case DEDUP_PSLG_VERTEX_REALLOC_ERROR:
    fprintf(stderr, "When deduplicating the PSLG vertices, realloc failed\n");
    break;
  case DEDUP_PSLG_EDGES_REALLOC_ERROR:
    fprintf(stderr, "When deduplicating the PSLG edges, realloc failed\n");
    break;
  case STL_HEADER_WRITE_ERROR:
    fprintf(stderr, "When writing to the header of an stl, writing failed\n");
    break;
  case STL_VECTOR_WRITE_ERROR:
    fprintf(stderr, "When writing a vector to an stl, writing failed\n");
    break;
  case RGB_BUFFER_MALLOC_ERROR:
    fprintf(stderr, "When allocating an rgb buffer, malloc failed\n");
    break;
  case LOAD_OPENGL_FUNCTION_ERROR:
    fprintf(stderr, "Loading OpenGL function failed\n");
    break;
  case OPENGL_SHADER_COMPILATION_ERROR:
    fprintf(stderr, "When compiling a shader an error occured\n");
    break;
  case OPENGL_SHADER_PROGRAM_LINK_ERROR:
    fprintf(stderr, "When linking a shader program an error occured\n");
    break;
  case DRAW_TRIANGULATION_MALLOC_ERROR:
    fprintf(stderr, "When drawing a trianglulation, malloc failed\n");
    break;
  case TRI_CLONE_ERROR:
    fprintf(stderr,
            "When using malloc to clone a triangulation, malloc failed\n");
    break;
  case TRI_CLONE_TRI_ERROR:
    fprintf(stderr, "When using malloc to clone the triangles within a "
                    "triangulation, malloc failed\n");
    break;
  case PDF_XREF_FIND_SEEK_END_ERROR:
    fprintf(stderr, "When trying to find the xref table in a pdf, fseek failed "
                    "to seek to the end\n");
    break;
  case PDF_XREF_FIND_FTELL_ERROR:
    fprintf(stderr,
            "When trying to find the xref table in a pdf, ftell failed\n");
    break;
  case PDF_XREF_FIND_SEEK_SET_ERROR:
    fprintf(stderr, "When trying to find the xref table in a pdf, fseek failed "
                    "to set the seek\n");
    break;
  case PDF_XREF_STARTXREF_NOT_FOUND:
    fprintf(stderr, "When trying to find the xref table in a pdf, the string "
                    "startxref was not found\n");
    break;
  case PDF_XREF_OFFSET_PARSE_ERROR:
    fprintf(stderr, "When trying to find the xref table in the pdf the offset "
                    "could not be properly parsed.\n");
    break;
  case PDF_XREF_FIND_FREAD_ERROR:
    fprintf(stderr,
            "When trying to find the xref table in a pdf, fread failed\n");
    break;
  case NEXT_STR_NOT_FOUND_ERROR:
    fprintf(stderr,
            "When using next_str, the character \"\\0\" was not found \n");
    break;
  case GET_XREF_FSEEK_ERROR:
    fprintf(stderr, "When getting the xref, fseek failed\n");
    break;
  case GET_XREF_FREAD_ERROR:
    fprintf(stderr, "When getting the xref, fread failed.\n");
    break;
  case GET_XREF_STRCHR_NEWLINE_FAIL:
    fprintf(stderr, "When getting xref, strchr to look at new line failed.\n");
    break;
  case NON_XREF_XREF:
    fprintf(stderr, "The type of the xref table is not an xref\n");
    break;
  case GET_XREF_STREAM_SEEK_ERROR:
    fprintf(stderr, "When getting the xref seeking the stream failed\n");
    break;
  case STREAM_DECOMPRESS_MALLOC_FAIL:
    fprintf(stderr, "Allocating memory for decompressed stream failed\n");
    break;
  case STREAM_DECOMPRESS_INIT_FAIL:
    fprintf(stderr, "Initializing the stream decompression failed\n");
    break;
  case STREAM_DECOMPRESS_FAIL:
    fprintf(stderr, "Decompressing streams failed\n");
    break;
  case GET_XREF_STREAM_MALLOC_ERROR:
    fprintf(
        stderr,
        "When getting the xref allocating memory to store the stream failed\n");
    break;
  case GET_XREF_STREAM_READ_ERROR:
    fprintf(stderr, "Reading the file to store the xref stream failed\n");
    break;
  case GET_XREF_MALLOC_ERROR:
    fprintf(stderr,
            "When getting the xref, allocating the PDFXref object failed\n");
    break;
  case GET_XREF_TABLE_ENTRIES_MALLOC_ERROR:
    fprintf(stderr, "When getting the xref table entries, malloc failed\n");
    break;
  case GL_GFX_DEVICE_CALLOC_ERROR:
    fprintf(stderr, "When using calloc to allocate memory for OpenGL "
                    "GfxDevice, calloc failed\n");
    break;
  default:
    fprintf(stderr, "SOMETHING BAD HAPPENED, WE DON'T KNOW WHAT\n");
    break;
  }
}

#ifdef _WIN32
#define CANIM_PLATFORM_WINDOWS 1
#define CANIM_PLATFORM_KNOWN 1
#endif
#ifdef __APPLE__
#define CANIM_PLATFORM_MAC 1
#define CANIM_PLATFORM_KNOWN 1
#endif
#ifdef __linux__
#define CANIM_PLATFORM_LINUX 1
#define CANIM_PLATFORM_KNOWN 1
#endif
#ifndef CANIM_PLATFORM_KNOWN
#define CANIM_PLATFORM_UNKNOWN
#endif
#endif
