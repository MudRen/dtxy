#include <ansi.h>

inherit ITEM;


void init()
{
      if(this_player()==environment())
        add_action("do_read", "read");
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
        set_name(HIW "����ת�澭��" NOR, ({"jiuzhuan zhenjing", "zhenjing"}));
        set_weight(5);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
set("no_give",1);
set("no_drop",1);
set("no_get",1);
                set("long", "һ�������������ľ�ת�澭�����������ơ�����\n");
                set("value", 10000);

        }
  
        set("is_monitored",1);
        setup();
}

int do_read(string arg)
{
        int i,j;

        object me = this_player();
  
        if (!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        

  

        

        i = random(1001);
        j = random(1001);


        message_vision(HIB "$N�Ȳ������ط����š���ת�澭���� \n�ߺ�ߴߴ�ض�����������ˮֱ����\n" NOR, me);  
//	if (!me->query("wizgift/jinchai")) 
//	{
	me->add("wizgift/jinchai",1);
me->add("daoxing",i+3000);
me->add("potential",i/10+300);
me->add("combat_exp",j+3000);
	log_file("static/jinchai","["+ctime(time())+"] "+
        sprintf("%s(%s)����%O\n",
         this_player()->query("name"),this_player()->query("id"),
 this_object()));
        
        tell_object (me,"��·�������Щ��������õ���"+COMBAT_D->chinese_daoxing(i+3000)+"����
��"+chinese_number(j+3000)+"����ѧ���Լ�"+chinese_number(i/10+300)+"��Ǳ�ܣ�
��������������
����ת�澭������һֻ�׺׳����ȥ���㲻�����겻�ѡ�\n");
//	}
        destruct(this_object());

        return 1;
        
}
