#include <ansi.h>
inherit ROOM;
void confirm_dispose(string arg, object ob, object fabao_ob);
void create()
{
	set("short",HIG "���Ｏ��" NOR);
	set("long",@LONG
������Ǳ������ĳ��Ｏ�У�����ʲô����Ϳ���
�õ�������������
LONG
	);
	
	set("exits", ([ /* sizeof() == 2 */
 
]));
 set("objects", ([ /* sizeof() == 2 */
  //__DIR__"obj/shu" : 1,
]));
	setup();
}
void init()
{
add_action("do_sell","sell");
}
int do_sell(string arg)
{
 object ob = this_player();
   object pet_ob;
   string pet_id;
    
   if (!ob->query("pet/pet_id"))
      return notify_fail("�㲢û�г������ʲô���֣�\n");
   pet_id=ob->query("pet/pet_id");
   if( !objectp(pet_ob=present(pet_id, ob)) && 
       !objectp(pet_ob=present(pet_id, environment(ob))))
      return notify_fail("��ĳ���û����һ������?\n");
      
   if(pet_ob->query("owner") != ob->query("id")) 
      return notify_fail("��......���������������Ү��\n");
      
   write("��ȷ��Ҫ�����"+pet_ob->query("name")+"������ȥ��(y/n)\n");
   input_to( (: confirm_dispose :), ob, pet_ob); 
   return 1;
}

void confirm_dispose(string arg, object ob, object pet_ob)
{
   string msg;
   int skl;
   if( arg == "y" || arg == "Y" ) 
     {
        if((int)pet_ob->query_skill("dodge",1) < 19 ||
           (int)pet_ob->query_skill("parry",1) < 19 ||
           (int)pet_ob->query_skill("unarmed",1) < 19)
          {
          write("��ĳ��Ｖ�𲻹�����������������\n"); 
          return;
          }
        skl=COMBAT_D->skill_power(pet_ob, "unarmed", 1)/100
           +COMBAT_D->skill_power(pet_ob, "unarmed", 2)
           +COMBAT_D->skill_power(pet_ob, "dodge", 2);
        skl+=pet_ob->query("zhongcheng")+pet_ob->query("tonicity")+pet_ob->query("cool")-pet_ob->query("sloth")+pet_ob->query("combat_exp")+pet_ob->query("daoxing");
        write("������"+skl+"\n"); 
        if (ob->query_temp("pet")==1)
               {
                ob->set_temp("pet",0);
                ob->delete_temp("ride/dodge");
               }
	ob->delete("pet");
msg=ob->name()+"�ڼ�����������"+pet_ob->name()+"���õ�"+skl+"����ѧ��"+COMBAT_D->chinese_daoxing(skl/2)+"���С�\n";
	message_vision(msg,pet_ob,ob);
	CHANNEL_D->do_channel(this_object(), "rumor",msg);
	destruct( pet_ob );
	
    }
  return;
}
