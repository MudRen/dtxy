#include <ansi.h>

inherit ITEM;


void init()
{
      if(this_player()==environment())
        
      call_out("announce",random(10),this_player());
}

void announce(object who)
{
    if(!this_object()) return;
    if(!who) return;
    CHANNEL_D->do_channel(this_object(), "rumor", 
            who->query("name")+"�õ���"+name()+"��\n");
}

void create()
{
set_name("��������������", ({"shengsibu", "bu"}));
        set_weight(5);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�����������������������ĵĹ⡣����\n");
                set("value", 10000);
                

        }
  
	set("special_effects", "none");  // emotion
        set("is_monitored",1);
        setup();
}
