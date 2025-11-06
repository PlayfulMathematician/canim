// SPDX-License-Identifier: MIT
#include "../../include/canim/core.h"
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
