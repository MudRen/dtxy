// lingzhi.c ǧ����֥
//

#include <ansi.h>
inherit ITEM;

void setup()
{}

int do_eat(string);
void destroy();
void init();
void init()
{
  if (!wizardp(this_player())) {
    set("no_get","������һ��"+this_object()->query("name")+"��ָ�们�䣡\n");
//     set("no_get","������һ��"+this_object()->query("name")+"��ָ�们�䣡\n");
    set("no_give","��ô����ҩ�����������ˣ�\n");
    set("no_drop","��ô����ĵ�ҩ�����˶��ϧѽ��\n");
    set("no_sell","��������֪��"+this_object()->query("name")+"�ļ�ֵ�������Լ����Űɡ�\n");
  }                                    
    add_action("do_eat", "eat");
    call_out("destroy", 120);
}
void create()
{
    set_name(HIB"��Ц�벽��"NOR, ({"hanxiao banbudian", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        set("unit", "��");
        set("long", "�������ζ�����һ���鵤����˵��ɱ�˱ر�֮��ҩ��\n");
		set("value", 0);
	}
	  set("is_monitored",1);
	setup();
}

int do_eat(string arg)
{
	  object me = this_player();
	  int force_add, howold;
  howold = (int)me->query("mud_age") + (int)me->query("age_modify");
        if (me->query("lestatgift/giftt"))
        {  
           tell_object(me,"��Ϊʲô��ô̰����?\n");
           destruct(this_object()); 
           return 1;
        }
        me->set("lestatgift/gift",1);
        me->save();
  	if (!id(arg))
	return notify_fail("��Ҫ��ʲô��\n");

    this_player()->add("combat_exp", 50000);
    this_player()->add("potential",100000);
    message_vision("$N����һ�ź��������ҩ��ͻȻ���˸���ƨ !\n", this_player());
	  if( howold > 1382400 ) {
    me->add("age_modify", -1200);
    me->add("age_modify_time", 1);
    me->add("eat/biou",1);
  }
  destruct(this_object());
  return 1;

}

void destroy()
{
  destruct(this_object());
}

