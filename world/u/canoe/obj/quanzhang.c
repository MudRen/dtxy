// ��ƽȨ��
// by canoe

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"��ƽȨ��" NOR, ({"staff" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
              set("long","�����ƽ���꣡��\n");
                set("value", 0);
        }
        setup();
}

void init()
{
        add_action("do_use","use");
}

int do_use(string arg)
{
        object me,*ob;
        int i;

        me = this_player();

        if( !arg || arg!="staff" )
                return notify_fail("what do you wanna use?\n");

        //if( me->is_fighting() )
                //return notify_fail("it's so irony, you are fighting ya!!\n");

        ob = all_inventory(environment(me));
 message_vision(HIY "$N����һ�������ϵؾ����˺�ƽȨ�ȣ�Ȩ�ȷ�����͵���⣡\n" NOR,me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || !ob[i]->is_fighting() ) continue;
       message_vision(CYN "��Ȩ�ȵ�����£�$N�������ε�ֹͣ��ս����\n"NOR ,ob[i]);
             ob[i]->remove_all_killer();
                add("num",1);
        }
                if(!query("num")) write("û��û���˴�ܣ��㷢ʲ��裿\n");
                        else delete("num");
                return 1;
}
