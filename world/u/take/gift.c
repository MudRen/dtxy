inherit NPC;
#include <ansi.h>
int give_gift();
void create()
{
    set_name(HIC"�����ʹ"NOR, ({ "da shi"}));
       set("age", 18+random(10));
       set("gender", "����");
  set("title", HIR"��������ר��"NOR);
       set("long","��λ�����ɾ������û�¸ɣ���ҹ����д����������ʹ�ߡ�\n");
        set("attitude", "peaceful");
  set("str", 50);
  set("kar", 50);
 set("per", 50);
      set("combat_exp", 200000000);
      set("daoxing", 200000000);
      set("max_force", 200000);
      set("max_mana", 200000);
set("max_kee", 40000);
set("max_sen", 40000);
set("force", 400000);
set("force_factor", 1000);
set("mana_factor", 1000);
set("mana", 1000);
       set_skill("unarmed", 1000);
        set_skill("dodge", 1000);
       set_skill("parry", 1000);
   set("inquiry",([
  "gift": (: give_gift :),
  "����": (: give_gift :),
   "����": (: give_gift :),
   "����": (: give_gift :),
]));
     setup();
}
int give_gift()
{
   object me;
   me=this_player();
        if(!me) return 0;
         if (me->query("take/����")=="2002")
{
message_vision("\n\n�����ʹ�ɻ�Ŀ���������㲻����������һ������ɣ�\n\n"NOR,me);
return 1;
}
           me->set("take/����","2002");
               if (me->query("combat_exp")<=100000)
me->add("potential",10000);
 if ((me->query("combat_exp")>=100001)&&(me->query("combat_exp")<=200000))
me->add("potential",30000);
               if (me->query("combat_exp")>200000)
me->add("potential",50000);
 message_vision("\n\n�����ʹ���ֺص���"+HIR"��   "+HIY"��   "+BLU"��   "+HIG"��   "+HIC"\n\n"+HIW"                       ��   "+HIB"��   "+HIC"��   "+HIM"��\n\n"NOR,me);
         write ("��2002�����굽��֮�ʣ���õ�����������ʦ�������ף�������Ǳ�������ˡ�\n");
return 1;
}
