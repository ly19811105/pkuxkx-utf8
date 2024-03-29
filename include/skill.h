// skill.h
#ifndef __SKILL__
#define __SKILL__

string query_skill_mapped(string skill);
varargs void map_skill(string skill, string mapped_to);
varargs int query_skill(string skill, mixed raw);
varargs void improve_skill(string skill, int amount, int weak_mode);

mapping query_skill_prepare();
mapping query_wprepare();

#endif
