
//vikee 
//damoyange.c you can add it to the directory /daemon/skill/yange-blade/
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
void damoyange_ok(object);
 
int perform(object me, object target)
{
        object weapon,weapon1;
        object* all = all_inventory(me);
        int ap,dp,damage;   
        string str;     
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С���Į��衹��\n");
         if( !wizardp(me) && me->query("family/family_name") != "��ׯ��" )
                return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���á���Į��衹?\n");

        if(!me->is_fighting(target))
                return notify_fail("����Į��衹ֻ����ս����ʹ�ã�\n");

        if((int)me->query("max_force") < 1500 )
                return notify_fail("�������������\n");

	if((int)me->query("force") < 1500 )
		return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
	all = filter(all, (: $1->query("music/type") == "xiao" :) );
	if( !sizeof(all) )
                return notify_fail("�����Ǵ����ˣ�\n");
        if((int)me->query_skill("yange-blade", 1) < 180)
                return notify_fail("�����赶�����𻹲�����ʹ����һ�л������ѣ�\n");
        if((int)me->query_skill("zhenyuan-force", 1) < 180)
                return notify_fail("�����赶�����𻹲�����ʹ����һ�л������ѣ�\n");
        if((int)me->query_skill("zouxiao", 1) < 180)
                return notify_fail("��Ĵ���֮���𻹲�����ʹ����һ�л������ѣ�\n");      
        if((int)me->query_skill("xiaofeng-sword", 1) < 180)
                return notify_fail("���������½����𻹲�����ʹ����һ�л������ѣ�\n");      
        //if (me->query_skill_mapped("force")!="zhenyuan-force")
        //        return notify_fail("��Į�����������Ԫ�񹦲���ʹ�á�\n");
        if (me->query_skill_mapped("sword")!="xiaofeng-sword")
                return notify_fail("��Į���������������½�����ʹ�á�\n");
        if( me->is_busy() )
		return notify_fail("����æ���أ������б��ݵĹ���\n");
 	if( target->is_busy() )
		return notify_fail("�Է���æ���أ�û�б�Ҫ���ı��ݡ�\n");
	weapon = all[0];
	weapon1 = me->query_temp("weapon");
	ap = me->query_skill("blade")/2 + me->query_skill("zouxiao",1);
	dp = target->query_skill("dodge")/3 + target->query_skill("force",1);
	message_vision(HIY"\n��ս��$NͻȻȫ������һ������$n����������\n"NOR,me,target);	
	me->set_temp("dmyg",1);
	COMBAT_D->do_attack(me,target, weapon1);
	me->delete_temp("dmyg");
	weapon1->unequip();
	weapon->wield();
	message_vision(HIC"\n$N�û��������֣����ְγ�" + weapon->name() + HIC"�����������������ɣ����һ��"+HIY"[��Į���]"+HIC"��\n"NOR,me,target);
	message_vision(YEL"\n��һ���������ã����Į���\n\n\t\t"+RED"��Į����ֱ����������Բ��\n"NOR,me,target);
	if( random(ap) > dp/3 )
	{
		target->start_busy(3+random(3));
		message_vision(YEL"\n$n��ǰ����������������ɿ�仯��$n�����������У���Ȼ���ң�\n"NOR,me,target);	
	}
	message_vision(HIC"\n$N����ͻ�䣬��תϸ�壬�������ҡ����ǵ�������������ǰ���¡���\n"NOR,me,target);
	if( target->is_busy() )
	{
		message_vision(HIC"\n$n��ǰ������֮ͻ�䣬$nһ��������������������$N����������Ծ����\n"NOR,me,target);
		message_vision(HIC"\n$N�����ٱ䣬Խ��Խϸ��Խ��Խ�ߣ��·����������ƶˣ����������\n"NOR,me,target);
		message_vision(HIR"\n$n����һĨ�������������ۡ����³�һ����Ѫ����Ȼ��$N�������˾�����\n"NOR,me,target);
		damage=ap + random(ap) - random(dp/2);
		if( damage < ap/2 ) damage = ap/2;
		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
		COMBAT_D->report_status(target);
	}
	else if( random(ap+dp) > dp/2 )
	{
		target->start_busy(2+random(2));
		message_vision(HIC"\n$n���������ֿ�$N������ɽ������֮���⣬����$N����֮���Ѿ������뻯��ת��֮���Ȼ��ɣ��޼���Ѱ��\n"NOR,me,target);
		message_vision(CYN"\n$n�Ͻ���ת�ķ���Ҫ�����������ļ�����������Ϣ��һʱ�������ã�\n"NOR,me,target);
	}
	else
	{
		message_vision(HIC"\n$nѭ��$N�������������磬���������ʮ�����ܣ�\n"NOR,me,target);
	}
	message_vision(HIC"\n$N������ͷһƬ������������µ��գ��ʻ�ŭ�ţ�\n"NOR,me,target);
	message_vision(HIC"\n$N�����������������к�Ȼ֮���̳�һ����\n"NOR,me,target);
	me->set_temp("XFS_perform",1);
	COMBAT_D->do_attack(me,target, weapon);
	me->delete_temp("XFS_perform");
	weapon->unequip();
	weapon1->wield();
        me->receive_damage("sen", ap/5);
        //me->add("force", -me->query_skill("yange-blade", 1));
	//me->start_busy(1+random(2));
	me->add("force", -ap/5);
	me->start_busy(1);
	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
        {
		str=target->name()+"��"+me->name()+"����ׯ�۾�ѧ"+HIY+"����Į��衹"+HIM+"���ȫ������������Ѫ������";
		message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
        return 1;
}


