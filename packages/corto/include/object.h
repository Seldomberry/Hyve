/*
 * corto_object.h
 *
 *  Created on: Aug 2, 2012
 *      Author: sander
 */

#ifndef CORTO_OBJECT_H_
#define CORTO_OBJECT_H_

#include "core/_type.h"
#include "lang/_type.h"
#include "secure/_type.h"
#include "corto/value.h"
#include "corto/async.h"
#include "corto/time.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef char corto_id[CORTO_MAX_PATH_LENGTH];
typedef int (*corto_scopeWalkAction)(corto_object o, void* userData);
typedef corto_equalityKind ___ (*corto_equalsAction)(corto_type _this, const void* o1, const void* o2);

/* Object lifecycle */
corto_object _corto_create(corto_type type);
corto_object _corto_createChild(corto_object parent, corto_string id, corto_type type);
corto_object _corto_createOrphan(corto_object parent, corto_string id, corto_type type);
corto_object _corto_declare(corto_type type);
corto_object _corto_declareChild(corto_object parent, corto_string id, corto_type type);
corto_object _corto_declareOrphan(corto_object parent, corto_string id, corto_type type);
corto_int16 corto_define(corto_object o);
corto_int16 corto_delete(corto_object o);

/* Object notifications */
corto_int16 corto_update(corto_object observable);
corto_int16 corto_updateBegin(corto_object observable);
corto_int16 corto_updateTry(corto_object observable);
corto_int16 corto_updateEnd(corto_object observable);
corto_int16 corto_updateCancel(corto_object observable);
corto_int16 corto_invalidate(corto_object o);
/* Publish event without reference to an object */
corto_int16 corto_publish(
    corto_eventMask event,
    corto_string id,
    corto_string type,
    corto_string contentType,
    void *content);

/* Memory management */
corto_int32 corto_claim(corto_object o);
corto_int32 corto_release(corto_object o);
void corto_setref(void* ptr, corto_object value);
void corto_setstr(corto_string* ptr, corto_string value);

/* Set/get object attributes for current thread */
corto_attr corto_setAttr(corto_attr attr);
corto_attr corto_getAttr(void);

/* Security */
corto_string corto_login(corto_string username, corto_string password);
corto_string corto_authenticate(corto_string key);
corto_bool corto_authorized(corto_object object, corto_secure_actionKind access);
corto_bool corto_authorizedId(corto_string id, corto_secure_actionKind access);
corto_bool corto_secured(void);

/* Object metadata */
corto_type corto_typeof(corto_object o);
corto_int32 corto_countof(corto_object o);
corto_state corto_stateof(corto_object o);
corto_attr corto_attrof(corto_object o);
corto_bool corto_checkState(corto_object o, corto_int8 state);
corto_bool corto_checkAttr(corto_object o, corto_int8 attr);
corto_bool _corto_instanceof(corto_type type, corto_object o);
corto_bool _corto_instanceofType(corto_type type, corto_type valueType);

/* Object metadata for scoped objects */
corto_string corto_idof(corto_object o);
corto_string corto_nameof(corto_id str, corto_object o);
corto_object corto_parentof(corto_object o);
corto_bool corto_childof(corto_object p, corto_object o);
corto_uint32 corto_scopeSize(corto_object o);
corto_objectseq corto_scopeClaim(corto_object o);
corto_objectseq corto_scopeClaimWithFilter(corto_object scope, corto_type type, corto_string id);
void corto_scopeRelease(corto_objectseq scope);
corto_int16 corto_scopeWalk(corto_object o, corto_scopeWalkAction action, void *userData);

/* Ownership */
corto_object corto_ownerof(corto_object o);
corto_bool corto_owned(corto_object o);
/* Set/get owner for thread */
corto_object corto_setOwner(corto_object owner);
corto_object corto_getOwner(void);

/* Object path */
corto_string corto_fullpath(corto_id str, corto_object o);
corto_string corto_fullname(corto_id str, corto_object o);
corto_string corto_path(corto_id str, corto_object from, corto_object o, const char* sep);
corto_string corto_pathname(corto_id str, corto_object from, corto_object o, const char* sep);
corto_int32 corto_pathToArray(corto_string path, char *elements[], char *sep);
corto_string corto_cleanpath(corto_id buffer, char* path);

/* Find objects by id */
corto_object corto_lookup(corto_object scope, corto_string id);
corto_object corto_resolve(corto_object scope, corto_string id);

/* Iterate over objects matching an expression */
typedef struct corto_selectFluent {
    struct corto_selectFluent (*contentType)(corto_string contentType);
    struct corto_selectFluent (*limit)(corto_uint64 offset, corto_uint64 limit);
    struct corto_selectFluent (*augment)(corto_string filter);
    struct corto_selectFluent (*type)(corto_string filter);
    struct corto_selectFluent (*fromNow)(void);
    struct corto_selectFluent (*fromTime)(corto_time t);
    struct corto_selectFluent (*fromSample)(corto_uint64 sample);
    struct corto_selectFluent (*toNow)(void);
    struct corto_selectFluent (*toTime)(corto_time t);
    struct corto_selectFluent (*toSample)(corto_uint64 sample);
    struct corto_selectFluent (*forDuration)(corto_time t);
    struct corto_selectFluent (*forDepth)(corto_int64 depth);
    corto_int16 ___ (*iter)(corto_resultIter *ret);
    corto_int16 ___ (*iterObjects)(corto_objectIter *ret);
    corto_int64 ___ (*count)(void);
} corto_selectFluent;
struct corto_selectFluent corto_select(corto_string scope, corto_string expr);

/* Observe objects for an observable matching an eventmask */
typedef struct corto_observeFluent {
    struct corto_observeFluent (*disabled)(void);
    struct corto_observeFluent (*dispatcher)(corto_dispatcher dispatcher);
    struct corto_observeFluent (*instance)(corto_object instance);
    struct corto_observeFluent (*type)(corto_string type);
    corto_observer ___ (*callback)(void (*r)(corto_object, corto_eventMask, corto_object, corto_observer));
} corto_observeFluent;
struct corto_observeFluent corto_observe(corto_eventMask event, corto_object observable);
corto_int16 corto_unobserve(corto_observer observer);

/* Subscribe for notifications matching an expression and eventmask */
typedef struct corto_subscribeFluent {
    struct corto_subscribeFluent (*disabled)(void);
    struct corto_subscribeFluent (*dispatcher)(corto_dispatcher dispatcher);
    struct corto_subscribeFluent (*instance)(corto_object instance);
    struct corto_subscribeFluent (*contentType)(corto_string contentType);
    struct corto_subscribeFluent (*type)(corto_string type);
    corto_subscriber ___ (*callback)(void (*r)(corto_object, corto_eventMask, corto_result*, corto_subscriber));
} corto_subscribeFluent;
struct corto_subscribeFluent corto_subscribe(corto_eventMask mask, corto_string scope, corto_string expr);
corto_int16 corto_unsubscribe(corto_subscriber subscriber, corto_object instance);

/* Match corto expression */
typedef struct corto_matchProgram_s* corto_matchProgram;
corto_bool corto_match(corto_string expr, corto_string str);
corto_matchProgram corto_matchProgram_compile(corto_string expr, corto_bool allowScopes, corto_bool allowSeparators);
corto_bool corto_matchProgram_run(corto_matchProgram program, corto_string str);
void corto_matchProgram_free(corto_matchProgram matcher);
/* Match parent of expression. Returns NULL if no match, or ptr to remainder (for corto_match) */
char* corto_matchParent(char *parent, char *expr);

/* Serialize object to contentType */
corto_string corto_contentof(corto_id str, corto_string contentType, corto_object o);
corto_int16 corto_fromcontent(corto_object o, corto_string contentType, corto_string content, ...);
corto_object corto_createFromContent(corto_string contentType, corto_string content);

/* Object extensions (Object Local Storage) */
corto_uint8 corto_olsKey(void(*destructor)(void*));
void* corto_olsSet(corto_object o, corto_int8 key, void *data);
void* corto_olsGet(corto_object o, corto_int8 key);
/* Thread-safe way to modify OLS data */
void* corto_olsLockGet(corto_object o, corto_int8 key);
void corto_olsUnlockSet(corto_object o, corto_int8 key, void *value);

/* Augment data (unstable API) */
corto_int16 _corto_augment(corto_type t, corto_string id, corto_mount r);

/* Read locking */
corto_int16 corto_readBegin(corto_object object);
corto_int16 corto_readEnd(corto_object object);

/* Write locking */
corto_int16 corto_lock(corto_object object);
corto_int16 corto_unlock(corto_object object);

/* REPL functionality (unstable API) */
corto_int16 corto_expr(corto_object scope, corto_string expr, corto_value *value);

/* Serialize to string */
corto_string corto_str(corto_object object, corto_uint32 maxLength);
corto_string corto_strv(corto_value* v, corto_uint32 maxLength);
corto_string _corto_strp(void *p, corto_type type, corto_uint32 maxLength);
corto_string corto_stra(corto_any a, corto_uint32 maxLength);

/* Deserialize from string */
corto_int16 corto_fromStr(void *o, corto_string string);
corto_int16 corto_fromStrv(corto_value *v, corto_string string);
corto_int16 _corto_fromStrp(void *p, corto_type type, corto_string string);
corto_int16 corto_fromStra(corto_any *a, corto_string string);

/* Copy */
corto_int16 _corto_copy(corto_object *dst, corto_object src);
corto_int16 corto_copyv(corto_value *dst, corto_value *src);
corto_int16 _corto_copyp(void *dst, corto_type type, void *src);
corto_int16 corto_copya(corto_any *dst, corto_any src);

/* Compare */
corto_equalityKind corto_compare(corto_object o1, corto_object o2);
corto_equalityKind corto_comparev(corto_value *v1, corto_value *value2);
corto_equalityKind _corto_comparep(void *p1, corto_type type, void *p2);
corto_equalityKind corto_comparea(corto_any a1, corto_any a2);

/* Init */
corto_int16 corto_init(corto_object o);
corto_int16 corto_initv(corto_value *v);
corto_int16 _corto_initp(void *v, corto_type type);
corto_int16 corto_inita(corto_any a);

/* Deinit */
corto_int16 corto_deinit(corto_object o);
corto_int16 corto_deinitv(corto_value *v);
corto_int16 _corto_deinitp(void *v, corto_type type);
corto_int16 corto_deinita(corto_any a);

/* Macro's that automate casting of parameters */
#define corto_create(type) _corto_create(corto_type(type))
#define corto_createChild(parent, name, type) _corto_createChild(parent, name, corto_type(type))
#define corto_createOrphan(parent, name, type) _corto_createOrphan(parent, name, corto_type(type))
#define corto_declare(type) _corto_declare(corto_type(type))
#define corto_declareChild(parent, name, type) _corto_declareChild(parent, name, corto_type(type))
#define corto_declareOrphan(parent, name, type) _corto_declareOrphan(parent, name, corto_type(type))
#define corto_strp(p, type, maxLength) _corto_strp(p, corto_type(type), maxLength)
#define corto_fromStrp(out, type, string) _corto_fromStrp(out, corto_type(type), string)
#define corto_copy(dst, src) _corto_copy((corto_object*)dst, src)
#define corto_copyp(p, type, src) _corto_copyp(p, corto_type(type), src)
#define corto_comparep(p1, type, p2) _corto_comparep(p1, corto_type(type), p2)
#define corto_initp(p, type) _corto_initp(p, corto_type(type))
#define corto_deinitp(p, type) _corto_deinitp(p, corto_type(type))
#define corto_instanceof(type, o) _corto_instanceof((corto_type)type, o)
#define corto_instanceofType(type, valueType) _corto_instanceofType((corto_type)type, (corto_type)valueType)
#define corto_augment(t, id, r) _corto_augment(corto_type(t), id, corto_mount(r))

#ifdef __cplusplus
}
#endif

#endif /* CORTO_OBJECT_H_ */
