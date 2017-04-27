/* $CORTO_GENERATED
 *
 * route.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/core/core.h>

/* $header() */
static corto_routerimpl corto_route_findRouterImpl(corto_route this) {
    corto_interface base = corto_interface(corto_parentof(this));
    do {
        if (corto_instanceof(corto_routerimpl_o, base)) {
            break;
        }
    } while ((base = base->base));
    return corto_routerimpl(base);
}
/* $end */

int16_t _corto_route_construct(
    corto_route this)
{
/* $begin(corto/core/route/construct) */
    corto_id pattern;
    char *ptr = pattern;
    corto_int32 count = 0, elementCount = 0;
    corto_routerimpl router = corto_route_findRouterImpl(this);
    corto_router routerBase = corto_router(corto_typeof(router));
    char *elements[CORTO_MAX_SCOPE_DEPTH];
    corto_int32 i;
    corto_parameterseq *params = &corto_function(this)->parameters;

    if (this->pattern) {
        strcpy(pattern, this->pattern);
        if (*ptr == '/') {
            ptr ++;
        }

        if (routerBase->elementSeparator) {
            if ((elementCount = corto_pathToArray(ptr, elements, routerBase->elementSeparator)) == -1) {
                corto_seterr("invalid pattern '%s': %s", this->pattern, corto_lasterr());
                goto error;
            }

            this->elements.buffer = corto_alloc(elementCount * sizeof(corto_string));
            this->elements.length = elementCount;
            for (i = 0; i < elementCount; i ++) {
                this->elements.buffer[i] = corto_strdup(elements[i]);
            }
        }
    }

    if (routerBase->paramType) {
        params->buffer = corto_realloc(
          params->buffer, sizeof(corto_parameter) * (count + 1)
        );
        corto_parameter *p = &params->buffer[count];
        memset(p, 0, sizeof(corto_parameter));
        corto_setref(&p->type, routerBase->paramType);
        if (routerBase->paramName) {
            corto_setstr(&p->name, routerBase->paramName);
        } else if (corto_checkAttr(routerBase->paramType, CORTO_ATTR_SCOPED)) {
            corto_setstr(&p->name, corto_idof(routerBase->paramType));
            p->name[0] = tolower(p->name[0]);
        } else {
            corto_setstr(&p->name, "_param");
        }
        count ++;
    }

    if (routerBase->routerDataType) {
        params->buffer = corto_realloc(
          params->buffer, sizeof(corto_parameter) * (count + 1)
        );
        corto_parameter *p = &params->buffer[count];
        memset(p, 0, sizeof(corto_parameter));
        corto_setref(&p->type, routerBase->routerDataType);
        if (routerBase->routerDataName) {
            corto_setstr(&p->name, routerBase->routerDataName);
        } else if (corto_checkAttr(routerBase->paramType, CORTO_ATTR_SCOPED)) {
            corto_setstr(&p->name, corto_idof(routerBase->routerDataType));
            p->name[0] = tolower(p->name[0]);
        } else {
            corto_setstr(&p->name, "_routerData");
        }
        count ++;
    }

    if (!strcmp(corto_idof(this), "_matched")) {
        corto_setref(&router->matched, this);
    }

    for (i = 0; i < this->elements.length; i++) {
        corto_string element = this->elements.buffer[i];
        if (element[0] == '$') {
            corto_function(this)->parameters.buffer = corto_realloc(
              corto_function(this)->parameters.buffer,
              (count + 1) * sizeof(corto_parameter)
            );
            corto_parameter *p = &corto_function(this)->parameters.buffer[count];
            memset(p, 0, sizeof(corto_parameter));
            corto_setref(&p->type, corto_string_o);
            corto_setstr(&p->name, &element[1]);
            count ++;
        }
    }

    corto_setref(&corto_function(this)->returnType, routerBase->returnType);
    corto_function(this)->parameters.length = count;

    return corto_method_construct(this);
error:
    return -1;
/* $end */
}

int16_t _corto_route_init(
    corto_route this)
{
/* $begin(corto/core/route/init) */
    if (!corto_route_findRouterImpl(this)) {
        corto_seterr("parent of '%s' is not an instance of 'routerimpl'",
            corto_fullpath(NULL, this));
        goto error;
    }

    return corto_method_init(this);
error:
    return -1;
/* $end */
}
