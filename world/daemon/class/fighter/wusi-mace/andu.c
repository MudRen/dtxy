// /daemon/class/fighter/wusi-mace/andu
// �²ְ���
// ��Ҫ�Լ�ѧʲô����ȫ�öԷ����书�����Է�
// Ľ�ݾ�ѧ���Ǻǡ�����
// writted by jie 2001-2-12
//modi by lestat 2001-5-2

#include <ansi.h>

inherit SSERVER;
int perform(object me,object target)
{
	int damage, lvl, r_lvl,ap,dp;
	string msg;
	string limb,*limbs,attack_skill,attack;
	object weapon,weapon2;
	mapping action;
	int cd = 6;
	if( !target ) target = offensive_target(me);

	if(!target||!target->is_character() || !me->is_fighting(target) )
	return notify_fail("�²ְ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	if(!wizardp(me) && me->query("family/family_name") != "������" )
    return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���á��²ְ��ɡ�?\n");
	if( (int)me->query_skill("literate",1)<150)
	return notify_fail("��Ķ���ʶ�ֲ��ô�����о���ԣ��ò��ˡ��²ְ��ɡ���\n");
		
	if( (int)me->query_skill("wusi-mace",1)<150)
	return notify_fail("�����˽ﵷ�������죬����ʹ�á��²ְ��ɡ���\n");
	if( (int)me->query_skill("lengquan-force",1)<150)
	return notify_fail("�����Ȫ�񹦲�����񣬲���ʹ�á��²ְ��ɡ���\n");
	
        if( me->query("lunhui_zhuanshi") > 4 )
		cd = 5;
	if( time()-(int)me->query_temp("andu_end") < cd )
    return notify_fail("�����ö�Ͳ����ˣ�\n");                       
			
	if( (int)me->query("force")<1000)
	return notify_fail("����������̫��������ʹ�á��²ְ��ɡ���\n");
			
	msg=HIY"$N��һ���񣬼������������²ְ��ɡ�����ƶ�Ȼʩչ����\n\n"NOR;

	//me->start_busy(1);
	//target->start_busy(random(3));
//��һ��
ap = me->query("combat_exp")/1000;
dp = target->query("combat_exp")/3000;
if( random(ap+dp) > dp ) {	
	damage = (int)me->query_skill("wusi-mace",1);
	//if( damage > 300) damage = 300;
	//lvl = damage/100;
	//r_lvl = 1+random(lvl);
  	//if( r_lvl > 5 ) r_lvl = 5;
        damage = damage + me->query_skill("mace",1);
        damage = damage + me->query_str();
        damage = damage + random(damage)/3;
        damage = damage - target->query_temp("apply/armor");
        if( damage < me->query_skill("mace",1) ) damage = me->query_skill("mace",1);
	target->receive_damage("kee",damage);
	target->receive_wound("kee",damage/3);
	me->add("force",-damage/10);
		
	weapon=target->query_temp("weapon");
	weapon2= me->query_temp("weapon");
	if(objectp(weapon))
		attack_skill=weapon->query("skill_type");
	else
		attack_skill="unarmed";
	attack=target->query_skill_mapped(attack_skill);
	if(!attack)	attack=attack_skill;
	msg +=HIW"$NʩʩȻ�ݳ�$n��ѧ�ġ���"HIM+to_chinese(attack)+HIW"���������о����̣�������ԣ���Ȼ���Ȳ��ң�\n"NOR;

	limbs=target->query("limbs");
        limb = limbs[random(sizeof(limbs))];
	action=target->query("actions");
        if( !mapp(action) ) 
		{
		target->reset_action();
		action=target->query("action");
                
        }
	msg += action["action"]+"��\n";
	msg+=HIB"$n�벻�����Է��ݹ����Լ��ľ����ѧ����ʱ����ʧ�룡�����$l���"+action["damage_type"]+"����\n"NOR;
	msg=replace_string(msg,"$l",limb);
	if(objectp(weapon)) 
        msg=replace_string(msg,"$w",weapon2->query("name"));
	message_vision(msg, me, target);
	COMBAT_D->report_status(target, 0);
//�ڶ���
	msg=HIW"\n$N��ʽδ��,�������ֵݳ�һ�С���"HIM+to_chinese(attack)+HIW"�����˳��ᢣ���ʤ��ǧ��֮�⡣\n"NOR;
	limbs=target->query("limbs");
        limb = limbs[random(sizeof(limbs))];
	action=target->query("actions");
        if( !mapp(action) ) 
		{
		target->reset_action();
		action=target->query("action");
                
        }
	msg += action["action"]+"��\n";
	msg+=HIB"$nû���Լ�������ѧ��Ȼ������˲��ʹ������ʱ�Ļ����䣡\n"NOR;
	msg=replace_string(msg,"$l",limb);
	if(objectp(weapon)) 
    msg=replace_string(msg,"$w",weapon2->query("name"));
	message_vision(msg, me, target);
	target->receive_damage("sen",damage);
	target->receive_wound("sen",damage/3);
	COMBAT_D->report_sen_status(target, 0);
	me->add("force",-damage/10);
} else {
        //me->start_busy(1);
        msg += HIC"$n���쳤Ц:����Ū��!�����ʶʲô�����ڡ�\n" NOR;
        message_vision(msg, me, target);
        me->add("force",-100);
        }
	
	me->set_temp("andu_end",time());
	return 1;
}



