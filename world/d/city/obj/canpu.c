inherit ITEM;


void init()
{
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
        set_name("������������", ({"mingqi canpu", "canpu"}));
        set_weight(40);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ��������������,�����Ȼû�ж������룬�ѵ�������\n");
                set("unit", "��");
                set("value", 25000);
                    
        }
	set("special_effects", "none");  // emotion
}
