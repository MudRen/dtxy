# include <skill.h>
#include <ansi.h>

inherit ITEM;

void announce(object who)
{
    if(!this_object()) return;
    if(!who) return;
    CHANNEL_D->do_channel(this_object(), "rumor", 
            who->query("name")+"�õ���"+name()+"��\n");
}

void create()
{
        set_name(HIY "��"+ HIR "��" + HIM "��" + HIC"��"+ HIW"ʯ" NOR, ({"butian stone", "stone", "shi"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("no_sell",1);
                set("no_put",1);
                set("value",0);
                set("unit","��");
                set("long",
"һ������ͷ׵�Сʯ�ӣ��ƺ���ϸ����(duanxiang)֮�»ᷢ����ʡ�\n");
        }
        set("is_monitored",1);
        setup();

}
void init()
{
        //call_out("announce",random(10),this_player());
        add_action("do_study","duanxiang");
}

int do_study(string arg)
{
        object me,pearl;
        int i,j;
        me=this_player();
        j=10+random(10);
        if( !arg || (arg!="butian stone"
                        && arg!="stone"
                        && arg!="shi") )
                return notify_fail("��Ҫ��ʲô��\n");
 if( (int)me->query_skill("butian-force",1) >= 50)
 return notify_fail("��Ĳ����ķ����ߣ���ʲ���ʯ�ڵ������Զ�����������ˡ�\n");
        if(!me->query("m_success/����ʯ"))
                return notify_fail("��ʲ���ʯ��������ʾ��û�и�Ե��ȡ������¾�����\n");
        if(!me->query("m_success/�õ������ķ�")){
                message_vision("$Nϸϸ����$n��ֻ��$n����Խ��Խ���䣬������˸���ǧ���硣
$N�о���������Ҫ�������У�����һ�ȣ�һ��ůů��������ת��֫�ٺ���\n",me,this_object());
//   me->set_skill("butian-force",j);
   me->add_skill("butian-force",j);
                tell_object(me,"��õ���"+chinese_number(j)+"�β����ķ���\n");
                me->set("m_success/�õ������ķ�",1);
                return 1;
                }
                
        if( (int)me->query_skill("force",1) < 20)
                return notify_fail("����ڹ��ķ������������ܲ�����ʲ���ʯ��������\n");
        if( (int)me->query_skill("butian-force",1) >= 50)
                return notify_fail("��Ĳ����ķ����ߣ���ʲ���ʯ�ڵ������Զ�����������ˡ�\n");
        if( (int)me->query_skill("spells",1) < 20)
                return notify_fail("��ķ������������������򲻵���ʲ���ʯ�ڵ�������\n");
        if( (int)me->query("kee") < 30)
                return notify_fail("�����Ѫ���㣬�������ε���ȥ��\n");
        if( (int)me->query("sen") < 30)
                return notify_fail("��ľ��񲻼ã���������Թ�ȥ��\n");
        if( (int)me->query("force") <30)
                return notify_fail("����������㣬�����к����档\n");
        i=(int)me->query_kar()*(int)me->query("spi")*4;
        if( i>3000 ){
                i=3000;
        }

        if( (int)this_object()->query("learned") >= i) {
                message_vision("$N���е�$nͻ���߲�֮�⣬һ��ϼ������ʧȥ����ɫ��\n",me,this_object());
                if( pearl=new("/d/sea/obj/pearl")){
                        pearl->move(me);
                }
                destruct(this_object());
                return 1;
        }
        message_vision("$Nϸϸ����$n��ֻ�����Ƶ���ϼ���������С�\n",me,this_object());
        me->improve_skill("butian-force", random((int)me->query_int()/3 + (int)me->query_spi()/3)+1+random(8));
        me->receive_damage("kee",5);
        me->receive_damage("sen",30);
        me->add("force",-10);
        this_object()->add("learned",1);

        write("��Բ����ķ��������ƺ�������һ�㡣\n");
        return 1;
}

