#include <ansi.h>


int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, force_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("kusang-bang",1);

 	if(me->query("family/family_name") != "���޵ظ�")
		return notify_fail(HIG"�����������"+NOR"��ڤ�粻��֮�ܣ�\n");
        if( !(me->is_fighting(target) ))
                return notify_fail("�����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "stick")             
        	return notify_fail("ʹ�á����������ʱ����������Ÿ�����\n");

        if( skill < 100)
                return notify_fail("��ġ���ɥ�����ȼ�����, ����ʹ�á������������\n");

        if( me->query_skill("dodge",1) < 120 )
                return notify_fail("����Ṧ�������޷����á������������\n");
	if( me->query("force") < 100 )
                return notify_fail("����������㣡\n");
        if( target->query("force") < 100 )
                return notify_fail("�Է�û�������������ˣ�\n");

        msg = HIC"$NͻȻ��ɫ������࣬�۽�$n����ǰ���ſ��������żⳤ�������$n���ʺ�ҧȥ��\n"NOR;
        message_vision(msg, me, target);

 	ap = me->query("combat_exp")/10000;
        dp = target->query("combat_exp")/14000 ;
 	if(random(ap+dp) > dp/2)
        {
                msg = HIG "$nֻ�����ʺ�һ���ʹ��$N���ڿ���$n����Ѫ��\n"NOR;
                force_wound = skill + me->query_skill("force") + me->query_str();
                force_wound = force_wound + random(force_wound/3);
	 	force_wound = force_wound - target->query_temp("apply/armor");
	 	if( force_wound < me->query_skill("stick",1) ) force_wound = me->query_skill("stick",1);
	 	me->add("force",force_wound/5);
	 	if( me->query("force") > me->query("max_force")*2 ) me->set("force",me->query("max_force")*2);
	 	target->add("force",-force_wound/2);
	 	if( target->query("force")<0 ) target->set("force",0);
	        message_vision(msg, me, target);
	        COMBAT_D->report_status(target);
        }
        else
        {
                msg = HIG "ֻ��$n���Ų�æ������һ���������$N�������\n"NOR;
                message_vision(msg, me, target);
                me->add("force",-100);
	}
        me->start_busy(1+random(2));
        return 1;
}

