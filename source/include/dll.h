#ifndef _DLL_H
#define _DLL_H

struct dll;
struct dll_entry;

struct dll *dll_new(void);
void dll_destroy(struct dll *list);
struct dll_entry *dll_new_entry(void);
void dll_destroy_entry(struct dll_entry *entry);
struct dll_entry *dll_append(struct dll *list, void *data);

#endif /* _DLL_H */
