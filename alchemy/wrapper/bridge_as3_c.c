/* bridge_as3_c.c -- The C<->AS3 bridge helper functions
 */
#include "bridge_as3_c.h"

#include <string.h>

AS3_Val Number_class = NULL;
AS3_Val int_class = NULL;
AS3_Val String_class = NULL;
AS3_Val Boolean_class = NULL;
AS3_Val flash_utils_namespace = NULL;
AS3_Val getQualifiedClassName_method = NULL;
AS3_Val Array_class = NULL;

/* setup some useful constants */
void initialize_as3_constants()
{
  Number_class = get_class2(NULL, "Number");
  int_class = get_class2(NULL, "int");
  String_class = get_class2(NULL, "String");
  Boolean_class = get_class2(NULL, "Boolean");
  flash_utils_namespace = AS3_String("flash.utils");
  getQualifiedClassName_method = AS3_NSGetS(flash_utils_namespace, "getQualifiedClassName");
  Array_class = get_class2(NULL, "Array");
}

/* Useful for debugging. Keep it here for a while */
void safe_release(AS3_Val value, const char * file, int line)
{
  AS3_Release(value);
}

/*
* Get an actionscript class with the given namespace and class name
* in the format: package::ClassName
*/
AS3_Val get_class(const char * as_namespaceclass_path)
{
  /* TODO: Merge with get_class2()? */

  AS3_Val as_namespace;
  AS3_Val ret;
  const char * class_ptr = NULL;

  /* TODO might want to store classes in a table to save loading again */

  class_ptr = strstr(as_namespaceclass_path, "::");

  if (class_ptr > as_namespaceclass_path)
  {
    as_namespace = AS3_StringN(
        as_namespaceclass_path, (class_ptr - as_namespaceclass_path) / sizeof(char)
      );
    class_ptr = class_ptr + 2; /* Skip '::' */
  }
  else
  {
    as_namespace = NULL;
    class_ptr = as_namespaceclass_path;
  }

  ret = AS3_NSGetS(as_namespace, class_ptr);

  /* TODO check for failure getting class */

  if (as_namespace)
  {
    AS3_Release(as_namespace);
  }

  return ret;
}

/*
* Get an actionscript class with the given namespace and class name
* in the format: package (may be NULL), ClassName
*/
AS3_Val get_class2(const char * as_namespace_path, const char * as_class_path)
{
  AS3_Val as_namespace;
  AS3_Val ret;

  /* TODO might want to store classes in a table to save loading again */

  if (as_namespace_path)
  {
    as_namespace = AS3_String(as_namespace_path);
  }
  else
  {
    as_namespace = NULL;
  }

  ret = AS3_NSGetS(as_namespace, as_class_path);

  /* TODO check for failure getting class */

  if (as_namespace != NULL)
  {
    SAFE_RELEASE(as_namespace);
  }

  return ret;
}

/*
  TODO: Ugly workaround. Remove.
        See http://tinyurl.com/a9djb2
*/
BOOL is_null(AS3_Val val)
{
  BOOL result = FALSE;
  AS3_Val classNameVal = AS3_CallT(
      getQualifiedClassName_method,
      NULL,
      "AS3ValType",
      val
    );
  AS3_Malloced_Str className = AS3_StringValue(classNameVal);
  SAFE_RELEASE(classNameVal);

  result = (strncmp(className, "null", 4) == 0);

  free(className);

  return result;
}

/*
* Get a string and its size in bytes from given AS3 string.
* To push to Lua multibyte string, you should know not its length
* (as in str.length), but its size in bytes.
* You may pass NULL as size_in_bytes.
* It is up to you to call free() on returned pointer.
*/
AS3_Malloced_Str get_string_bytes(AS3_Val strValue, size_t * size_in_bytes)
{
  AS3_Malloced_Str str = AS3_StringValue(strValue);
  if (size_in_bytes != NULL)
  {
    /*
    * Note strlen() not mbstrlen().
    * We should get size in bytes, not in characters.
    */
    /*
    * TODO: UGLY HACK! Support embedded zeroes somehow.
    */
    *size_in_bytes = strlen(str);
  }
  return str;
}