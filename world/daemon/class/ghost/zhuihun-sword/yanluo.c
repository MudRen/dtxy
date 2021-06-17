//yanluo��������
//2001 lestat for zhuihun-sword

#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("���������ޡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if(me->query("family/family_name") != "���޵ظ�")
                return notify_fail("���������ޡ��ǵظ�����֮�ܣ�\n");

        if( me->query_temp("yunwu") )
                return notify_fail("���Ѿ�ʹ�����������ޡ��ˣ�\n");

        weapon = me->query_temp("weapon");
        if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽��������ʩչ���������ޡ���\n");

        if( me->query_skill("dodge") < 60 )
                return notify_fail("����Ṧ��Ϊδ��������ʩչ���������ޡ��ı��֮����\n");

        if( me->query_skill("sword") < 60 )
                return notify_fail("���ڽ����ϵ����費����ʹ�����������ޡ���\n");

        if( me->query("force") <= 200 )
                return notify_fail("�����������ʩչ���������ޡ���\n");

        skill = me->query_skill("sword");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	if(random(target->query_skill("parry"))>skill) 
	{
        	message_vision(HIW "\n$N����ʹ��"+HIR"���������ޡ�"+HIW"������$n�ϼӽ䱸��ȫ���Ż����޲��ر������������Ч��\n" NOR, me, target);
		me->start_busy(2);
	}
	else
	{
        	message_vision(HIC "\n�������ⶸ����$N����"+weapon->query("name")+HIC"ԽʹԽ�죬������ã�����׷�꽣����"+HIR"���������ޡ�"NOR+HIC"��\n" NOR, me, target);
        	me->set_temp("yunwu", 1);
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        	call_out("checking", 1, me, target);
        	me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/2);
	}
        me->add("force", -200);
        return 1;
}


void checking(object me, object target)
{

	object weapon;
	weapon = me->query_temp("weapon");

        if ( me->query_temp("yunwu")  ) {
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword") {
                tell_object(me, "\n������û�гֽ������������ޡ��Ĺ��Ʊ㼴�߽⣡\n" NOR);
		me->delete_temp("yunwu");
                return;
           }


           else if ( weapon->query("weapon_prop") == 0 ) {
                tell_object(me, "\n���"+weapon->name()+"�ѻ٣��޷��������������ޡ��Ĺ��ƣ�\n\n" NOR);
		me->delete_temp("yunwu");
                return;
           }
           else if ( (int)me->query("force") < 400  ) {
                tell_object(me, "\n���������̲��㣬���Գ������������ޡ���������ֻ���ջ����С�\n\n" NOR);
		me->delete_temp("yunwu");
                return;
           }
           else if ( me->query_skill_mapped("sword") != "zhuihun-sword" ) {
                tell_object(me, "\n��ת��ʩչ�����������޷����ԡ��������ޡ����У�\n\n" NOR);
		me->delete_temp("yunwu");
                return;
           }
           else if (!me->is_fighting()) {
                tell_object(me,  "\n������û�к��˹��У������ջ��ˡ��������ޡ��Ĺ��ơ�\n\n" NOR);
		me->delete_temp("yunwu");
                return;
           }
	   else call_out("checking", 1, me, target);
	}
	   else return;

}  

void remove_effect(object me, int amount)
{

        if ( me->query_temp("yunwu") ) {
                message_vision(HIW"\n$N���н������ѽ�һ�ס��������ޡ�ʹ�꣡\n" NOR, me);
        me->delete_temp("yunwu");
        }
}

