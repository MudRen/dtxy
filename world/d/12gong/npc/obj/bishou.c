// by ����(take)
#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
   set_name(HIR"ذ��"NOR, ({"bi shou", "shou", "bi"}));
   set_weight(0);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("unit", "��");
     set("long", "����һ�ѳ���а���ذ��,������񻹴���δ�ɵ�Ѫ����\n");
     set("value", 0);
     set("material", "steel");
     set("wield_msg", "$N�Ӿ���ȡ��һ��$n�������С�\n");
     set("unwield_msg", "$N�����е�$n���ؾ��ϡ�\n");
set("no_drop","���ȻҪ����,�α��ӵ�?\n");
    set("no_give","��ɱ�ŵ��ȵ�����,���������ˣ�\n");
}
   init_sword(50);
   setup();
}

void init()
{
  add_action("do_stab", "stab");
}

int do_stab(string arg)
{
  object me = this_player();
  object where = environment(me);
  object ob; 

  if (arg =="athena")
    {   
        me->start_busy(10);
		call_out("applying",1,me);     
	}
	 else
  return notify_fail ("���ذ��ֻ��������ɱ�ŵ���.\n");
	 
return 1;


}

void applying (object me)
{
  
  message_vision (RED"\n$N�����ĵؿ������޷�����Ů��-�ŵ���\n",me);
  message_vision (RED"\n�ŵ��ȷ���$N�е㲻��,�����ſ�ѯ��$N������.\n",me);
    message_vision (RED"\n\n$Nһ����������Ů��,��а���ذ������Ĳ�����ŵ��ȵ��ؿ�........\n",me);
	call_out("finish_kill",2,me);
}

void finish_kill(object me)
{
	message_vision (BLU"\n\n\n�ŵ��Ⱦ��ȵĿ�����,�����ĵ�����ȥ!\n"NOR,me);
    present("athena",environment(me))->unconcious();
    message("channel:rumor", HIM + "��ҥ�ԡ�ĳ�ˣ���˵Ů���ŵ��ȱ�"+me->query("family/family_name")+"��"+HIY""+
     me->query("name")+HIM"�����ˡ�\n"NOR,users());
    destruct (this_object());
}
 