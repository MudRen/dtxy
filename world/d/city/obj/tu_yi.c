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
        set_name("����ͼһ", ({"baowu tuyi", "tuyi"}));
        set_weight(40);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "ĳ�˻��ı���ͼ֮һ��\n");
                set("unit", "��");
                set("value", 1000);
                    
        }
	set("special_effects", "none");  // emotion
}
