//��ؾ�����հ��������ܾ����󷽹���Ͼ����������ٷ𾭡���������������ʮ���������ʮ���¾�������������ز�������Ը��
#include <ansi.h>

inherit SSERVER;
string* fojing = ({
	HIB"��ؾ�"NOR,
	HIY"��հ��������ܾ�"NOR,
	HIM"�󷽹���Ͼ�"NOR,
	WHT"�������ٷ�"NOR,
	RED"����������"NOR,
	HIG"��ʮ�����"NOR,
	BLU"��ʮ���¾�"NOR,
	HIW"�������"NOR,
	HIR"�ز�������Ը��"NOR,
});
string* zhenyan = ({"��","��","��","��","��","��",});
int perform(object me, object target)
{
        
	object weapon;
   	int damage,jiali;
	int enhance,damage1, mypot,tapot;
	int weapon_damage = me->query_temp("apply/damage");
	string str,xuename,dodge_skill;
        int cd = 10;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�⡸��ħͬ�����湦��\n");

        if(!me->is_fighting(target))
                return notify_fail("����ħͬ����ֻ����ս����ʹ�ã�\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("�������������\n");
      	if( !wizardp(me) && me->query("family/family_name") != "�Ϻ�����ɽ" )
                return notify_fail("�����Ķ�͵ѧ�����书��\n");

        if((int)me->query("force") < 1500 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
	if( !me->query("fmtd_known") )
		return notify_fail("�㻹û�������ħͬ�����湦��\n");
	enhance=(int)me->query_skill("huoyun-qiang",1);

        if( enhance < 200 )
                return notify_fail("���ǹ�����𻹲�����ʹ����һ�л������ѣ�\n");
        damage=(int)me->query_skill("lotusforce",1);
        if( damage < 200 )
                return notify_fail("����ķ����𻹲�����ʹ����һ�л������ѣ�\n");
	jiali = me->query("force_factor")+1;
	
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("fmtd_end") < cd )
                return notify_fail("��������Ϣ��˳��\n");
	mypot = (int)me->query("combat_exp")/10000;
	tapot = (int)target->query("combat_exp")/15000;
       	weapon = me->query_temp("weapon");
       	dodge_skill = target->query_skill_mapped("dodge");
	if( !dodge_skill ) dodge_skill = "dodge";
       	message_vision(HIB"\n$N��"+weapon->name()+NOR+HIB"һ�ڣ��Է����ڹ�Ϊ������ʩչ����"+HIR"����ǹ��"+HIB"����\n"NOR,me,target);
       	if( target->query("class") ==  "yaomo" )
       		message_vision(RED"\n$n��״�����һ��������ͺ����Ȼ͵����ʥ�ž�ѧ��\n"NOR,me,target);
       	else
       		message_vision(RED"\n$n��ɫһ�䣺�벻�������Ϻ����ӣ���Ȼ͵��ħ����\n"NOR,me,target);
       	xuename = fojing[random(sizeof(fojing))];
       	message_vision(CYN"\n$N����ׯ�ϣ����������������ʱ������������\n"NOR,me);
       	message_vision(CYN"$n���������$N���������"+xuename+CYN"��\n"NOR,me,target);
       	message_vision(HIC"$N������ţ�ָ��ض��ʣ���ν��ħ֮�֣���$n���ɵ�ͷ��˼��\n"NOR,me,target);
       	xuename = zhenyan[random(sizeof(zhenyan))];
       	message_vision(RED"\n$N�Ӷ�"+weapon->name()+NOR+RED"��ǹ���Ͻ��һ����������ԣ�"+BLINK+HIY+xuename+NOR+RED"��\n"NOR,me,target);
       	message_vision(RED"\n$N������ţ����Ծ�ֱ��$nӡȥ��\n"NOR,me,target);
        if( random( mypot ) > tapot/4 ) 
	{       
             	damage1 = damage + jiali;
             	me->add("force",-damage1/4);
             	damage1 = damage1 + random(enhance/3);
             	message_vision(HIR"\n���$n������ʵʵӡ��ǰ�أ��������һ����Ѫ��\n"NOR,me,target);
             	target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	COMBAT_D->report_status(target);
	}
	else
	{
		me->add("force",-60);
         	message_vision(YEL+SKILL_D(dodge_skill)->query_dodge_msg(target, 1)+NOR, me, target);
	}
	xuename = zhenyan[random(sizeof(zhenyan))];
	message_vision(CYN"\n������$N���һ����"+weapon->name()+NOR+CYN"������һ����īɽˮ���ݺ���б���������ʻӾ�һ����������ԣ�"+BLINK+HIR+xuename+NOR+CYN"��\n"NOR,me,target);
	message_vision(RED"\n���������â���ۣ�����ȴ���������ܣ���Х������$n��\n"NOR,me,target);
	if( random(mypot) > tapot/3 )
	{
		damage1 = damage + jiali / 2;
             	me->add("force",-damage1/5);
             	damage1 = damage1 + random(enhance/3);
             	message_vision(HIR"\n���$n������ʵʵӡ��ǰ�أ��������һ����Ѫ��\n"NOR,me,target);
	        target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	COMBAT_D->report_status(target);
	 	damage1 = enhance + jiali / 2;
	 	me->add("force",-damage1/5);
	 	damage1 = damage1 + random(damage/3);
	 	target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	message_vision(HIR"\n����������ϯ����Ͻ�$n�յý�ͷ�ö\n"NOR,me,target);
	 	COMBAT_D->report_status(target);
	}
	else if( random(mypot) > tapot/4 )
	{
		damage1 = damage + jiali;
             	me->add("force",-damage1/4);
             	damage1 = damage1 + random(enhance/3);
		message_vision(YEL"\n$n��æ�˹����壬�������������֮�⣡\n"NOR,me,target);
		message_vision(HIY"�����������̵ķ���������Ϊ���У�������$n�Ļ���������\n"NOR,me,target);
		target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	COMBAT_D->report_status(target);
	}
	else if( random(mypot) > tapot/5 )
	{
		message_vision(YEL"\n$nʶ������������һ�������������Ա�ס��\n"NOR,me,target);
		message_vision(HIR"�����������̵ķ�������ͻȻ�ŷ������汩�ǣ���$n�յý�ͷ�ö\n"NOR,me,target);
		damage1 = enhance + jiali;
             	me->add("force",-damage1/4);
             	damage1 = damage1 + random(damage/3);
             	target->receive_damage("kee",damage1,me);
	        target->receive_wound("kee",damage1/3,me);
	 	COMBAT_D->report_status(target);
	}
	else
	{
		me->add("force",-100);
         	message_vision(YEL+SKILL_D(dodge_skill)->query_dodge_msg(target, 1)+NOR, me, target);
	}
	if( me->query("fmtd_known") > 1 )
	{
		xuename = fojing[random(sizeof(fojing))];
		message_vision(HIC"\n$N����������"+xuename+HIC"��\n"NOR,me,target);
		message_vision(HIC"\n"+weapon->name()+NOR+HIC"�����ų�ҫ�۵Ĺ�â��\n"NOR,me,target);
		message_vision(HIC"�ǹ�â���Ⱥ����䣬������������������޼䣬�ٷֱ治��������ɫ��\n"NOR,me,target);
		message_vision(HIC"$N�����������ԣ�����ǹ�����������ǹ����\n"NOR,me,target);
		message_vision(HIC"ǹ����β������$n���ڵ��У�$n��ϸһ�������ǹ�����Ƿ�����ԡ�\n"NOR,me,target);
		message_vision(WHT"\n$N�����������ӷ𣡡��������Ӧ������$n��\n"NOR,me,target);
		if( random(mypot+tapot) > tapot/2 )
		{
			damage1 = damage + jiali + enhance;
			me->add("force",-damage1/4);
			damage1 = damage1 * 2 + random(damage1/3);
			message_vision(HIR"���$n���������ħ�������������Ի��У���̲�����������ȥ��\n"NOR,me,target);
	 		target->receive_damage("kee",damage1,me);
	        	target->receive_wound("kee",damage1/2,me);
	 		COMBAT_D->report_status(target);
		}
		else
		{
			me->add("force",-120);
	         	message_vision(YEL+SKILL_D(dodge_skill)->query_dodge_msg(target, 1)+NOR, me, target);
		}
	}
	//me->start_busy(2);       
	me->receive_damage("sen", 150);
	me->set_temp("fmtd_end",time());
        return 1;
}
