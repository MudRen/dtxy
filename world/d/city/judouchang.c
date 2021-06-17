#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short",HIR "������" NOR);
        set("long", @LONG
��������רΪ������������������ġ�����������������Ը�,���õ���
PK�����ǽ�����Ÿ�����(tiezi),�����ǹ��档
LONG );
        set("no_steal",1);
        set("no_beg",1);
        set("item_desc", ([
            "tiezi" : @TEXT

----------------------------------------------------------------------
���������ߣ�

����˫��ʹ�� juedou ��������Է��������˫��ͬ���ȿ�ʼ������
������ʤ���߿��� xiaochu ��������PK��¼�����ߺ���Ը���
                                            ������ʦС��
----------------------------------------------------------------------

TEXT
        ]) );
        set("exits", ([
"down" : "/d/city/wuguan",
        ]));
        setup();
}
void init()
{
	add_action("do_kill","juedou");
	add_action("do_xiaochu","xiaochu");
}
int do_kill(string arg)
{
	object obj, old_target;
	object me;
	me = this_player();
	if(!arg || !objectp(obj = present(arg, environment(me))))
		return notify_fail("���빥��˭��\n");
	if( !obj->is_character() )
		return notify_fail("�����һ�㣬�ǲ��������\n");
	if( obj->is_fighting(me) )
		return notify_fail("���ͣ����ͣ����ͣ�\n");
	if( !living(obj) )
		return notify_fail(obj->name() + "�Ѿ��޷�ս���ˡ�\n"); 
	if(obj==me)	return notify_fail("�㲻�ܹ����Լ���\n");
	if( userp(obj) && (object)obj->query_temp("pending/fight")!=me ) {
		message_vision("\n$N����$n˵����" 
			+ RANK_D->query_self(me) 
			+ me->name() + "��������"
			+ RANK_D->query_respect(obj) + "��һ������\n\n", me, obj);
		if( objectp(old_target = me->query_temp("pending/fight")) )
			tell_object(old_target, YEL + me->name() + "ȡ���˺����������ͷ��\n" NOR);
		me->set_temp("pending/fight", obj);
		tell_object(obj, YEL "�����Ը��ͶԷ����о���������Ҳ��" + me->name() + "("+(string)me->query("id")+")"+ "��һ�� juedou ָ�\n" NOR);
		write(YEL "�����ȶԷ�ͬ����ܽ��о�����\n" NOR);
		return 1;
	}
	if( obj->query("can_speak") ) {
		message_vision("\n$N����$n˵����" 
                        + RANK_D->query_self(me) 
                        + me->name() + "��������"
                        + RANK_D->query_respect(obj) + "��һ������\n\n", me, obj);
		notify_fail("������" + obj->name() + "��������������\n");
		if( !userp(obj) && !obj->accept_fight(me) ) return 0;
		me->kill_ob(obj);
		me->set_temp("juedou/pks", me->query("PKS"));
		me->set_temp("juedou/number", 1);
		obj->kill_ob(me);
		obj->set_temp("juedou/pks", me->query("PKS"));
		obj->set_temp("juedou/number", 1);
	} else {
		message_vision("\n$N���һ������ʼ��$n����������\n\n", me, obj);
		me->kill_ob(obj);
		me->set_temp("juedou/pks", me->query("PKS"));
		me->set_temp("juedou/number", 1);
		obj->kill_ob(me);
		obj->set_temp("juedou/pks", me->query("PKS"));
		obj->set_temp("juedou/number", 1);
	}
        write_file("/log/static/ATTEMP_KILL",sprintf("%s   ��ͼ��   %s ���� on %s\n",
        me->name(1),obj->name(1), ctime(time()) ));
	return 1;
}

int do_xiaochu()
{
	object me;
	me = this_player();
	if( me->query_temp("juedou/number") == 1)
{
		if ( me->query_temp("juedou/pks")+1 == me->query("PKS")) //��֤PK��¼
{
		tell_object(me,"���PK��¼�����ˡ�\n");
		me->add("PKS", -1);
		me->delete_temp("juedou");
		return 1;
}
	        tell_object(me,"����û�зֳ�ʤ���ɣ�\n");
	        return 1;
}
	tell_object(me,"��Ϲ����ʲô��\n");
                return 1;
}

int valid_leave(object me, string dir)
{
	me->delete_temp("juedou");
        return ::valid_leave(me, dir);
}
