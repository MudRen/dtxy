
#include <ansi.h>
string give_reward(object me) {
  mapping skill=me->query_skills();
  string *skillnames;
  string selected,msg;
  int level, inc=0;
  if (!skill) return "none";
  //if(me->query("combat_exp")<100000)return " ";
  skillnames=keys(skill);
  selected=skillnames[random(sizeof(skillnames))];
  level=skill[selected];
  if(level<80) {
      inc=random(20)==0;
  } else if(level<160) {
      inc=random(40)==0;
  } else if(level<240) {
      inc=random(60)==0;
  } else {
      inc=random(80)==0;
  }
  if(inc==1) {
    me->set_skill(selected,level+1);
    tell_object(me,HIY"\n你得到了一级"+ to_chinese(selected) +"。\n"NOR);
    return selected;
  }
  return "none";
}
