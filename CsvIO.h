/*
** 2015 February 5
**
** The author, John Soprych, disclaims copyright to this source code.
** In place of a legal notice, here is an also borrowed blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains a C++ wrapper around some cvs field parsing code
** from the freeware "sqlite" command line utility for database access.
*/

#ifndef CSVIO_H
#define CSVIO_H

#include <stdio.h>
#include <string>
#include <vector>

/*
** An object used to read a CSV and other files for import.
*/
//typedef struct ImportCtx ImportCtx;
struct ImportCtx {
  const char *zFile;  /* Name of the input file */
  FILE *in;           /* Read the CSV text from this input stream */
  std::string z; //char *z;            /* Accumulated text for a field */
  int n = 0;          /* Number of bytes in z */
  // int nAllocbv = 0;   /* Space allocated for z[] */
  int nLine = 0;      /* Current line number */
  int cTerm = 0;      /* Character that terminated the most recent field */
  int cColSep = ',';  /*  rfc4180 column separator character.  (Usually ",") */
  int cRowSep = '\n';    /*  rfc4180 row separator character.  (Usually "\n") */

  friend std::ostream& operator << (std::ostream& os, const ImportCtx& ic){
    os << "zFile: " << ic.zFile << ", "
       << "in" << ic.in << ", "
       << "n: " << ic.n << ", "
       << "z: " << ic.z << ", "
       << "nLine: " << ic.nLine << ", "
       << "cTerm: " << ic.cTerm << ","
       << "cColSep: " << ic.cColSep << ","
       << "cRowSep: " << ic.cRowSep << std::endl;

    return os;
  }
};

/*
** True if an interrupt (Control-C) has been received.
*/

typedef std::vector<std::string> VStr;
typedef std::vector<VStr> VVStr; // vector of string vectors

std::ostream& operator << (std::ostream& os, const VVStr& vvs){
  // assuming uniform cop and row length
  char DELIM = '|';
  int col_len = vvs.size();
  if(col_len){
    int row_len = vvs[0].size();
    for(int r = 0; r < row_len; r++){
      for(int c = 0; c < col_len; c++){
        if(c){os << DELIM;}
        os << vvs[c][r];
      }
      os << std::endl;
    }
  }
  return os;
}

class CsvIO
{
  ImportCtx _pIC;
  VVStr _grid = {};

  public:
    /** Default constructor */
    CsvIO() {}
    /** Default destructor */
    virtual ~CsvIO() {}

    const char* test(){return "Yello";}

    bool readCvsFile(const char* filePath){
      _grid.clear();
      FILE * pFile;
      pFile = fopen (filePath,"r");
      if (pFile!=NULL){
        ImportCtx ic;
        ic.zFile = filePath;
        ic.in = pFile;

        int idx = 0;

        while(csv_read_one_field(&ic)){
          if(_grid.size() < (size_t)idx+1){
            VStr vs;
            _grid.push_back(vs);
          }
          VStr& vs = _grid[idx++];
          //std::cout << ic << std::endl;
          vs.push_back(ic.z);
          ic.z.clear();
          if( ic.cTerm != ic.cColSep ){ // reset field index after row
            idx = 0;
          }
        }
        fclose (pFile);
        std::cout << _grid;
        return true;
      }
      return false;
    }

    /* Read a single field of CSV text.  Compatible with rfc4180 and extended
    ** with the option of having a separator other than ",".
    **
    **   +  Input comes from p->in.
    **   +  (BEFORE)Store results in p->z of length p->n.  Space to hold p->z comes
    **      from sqlite3_malloc(). (NOW) store results in C++ string
    **   +  Use p->cSep as the column separator.  The default is ",".
    **   +  Use p->rSep as the row separator.  The default is "\n".
    **   +  Keep track of the line number in p->nLine.
    **   +  Store the character that terminates the field in p->cTerm.  Store
    **      EOF on end-of-file.
    **   +  Report syntax errors on stderr
    */
    //static char *csv_read_one_field(ImportCtx *p){
    static const char* csv_read_one_field(ImportCtx *p){
      int seenInterrupt = 0; //JS:

      int c;
      int cSep = p->cColSep;
      int rSep = p->cRowSep;
      p->n = 0;
      c = fgetc(p->in);
      if( c==EOF || seenInterrupt ){
        p->cTerm = EOF;
        return 0;
      }
      if( c=='"' ){
        int pc, ppc;
        int startLine = p->nLine;
        int cQuote = c;
        pc = ppc = 0;
        while( 1 ){
          c = fgetc(p->in);
          if( c==rSep ) p->nLine++;
          if( c==cQuote ){
            if( pc==cQuote ){
              pc = 0;
              continue;
            }
          }
          if( (c==cSep && pc==cQuote)
           || (c==rSep && pc==cQuote)
           || (c==rSep && pc=='\r' && ppc==cQuote)
           || (c==EOF && pc==cQuote)
          ){
            do{ p->n--; }while( p->z[p->n]!=cQuote );
            p->cTerm = c;
            break;
          }
          if( pc==cQuote && c!='\r' ){
            fprintf(stderr, "%s:%d: unescaped %c character\n",
                    p->zFile, p->nLine, cQuote);
          }
          if( c==EOF ){
            fprintf(stderr, "%s:%d: unterminated %c-quoted field\n",
                    p->zFile, startLine, cQuote);
            p->cTerm = c;
            break;
          }
          p->z += (char)c; //import_append_char(p, c);
          ppc = pc;
          pc = c;
        }
      }else{
        while( c!=EOF && c!=cSep && c!=rSep ){
          p->z += (char)c; //import_append_char(p, c);
          c = fgetc(p->in);
        }
        if( c==rSep ){
          p->nLine++;
          if( p->n>0 && p->z[p->n-1]=='\r' ) p->n--;
        }
        p->cTerm = c;
      }
      // JS: NIT NEEDED WITH C++ string vs C string
      // if( p->z ) p->z[p->n] = 0;
      return p->z.c_str(); //return p->z;
    }

    /* Append a single byte to z[] */
    //static void import_append_char(ImportCtx *p, int c){
    //  p->z += (char)c;
      /*
      if( p->n+1>=p->nAlloc ){
        p->nAlloc += p->nAlloc + 100;
        p->z = sqlite3_realloc(p->z, p->nAlloc);
        if( p->z==0 ){
          fprintf(stderr, "out of memory\n");
          exit(1);
        }
      }

      p->z[p->n++] = (char)c;
      */
    //}

  protected:
  private:
};

#endif // CSVIO_H
