// /daemon/class/yaomo/kusong/wuyue-spear/fengchan  ��������
// writted by jie 2001-2-8
// ������ ��������ȡ���Ϲ��˵۶���������
// ������������5�У�������� ƽ����ӹ ���º�� �������� ��������
// ��l=(int)me->query_skill("literate",1)�й�
// ������ʼ������3�� ������� �������� ��������
// �����ܷ����ı�ɱ�� ������������ɽ
#include <ansi.h>
#include <combat.h>

inherit SSERVER;

int calculate_damage(object me, object target, int base_damage, int damge_bonus);
int perform(object me, object target)
{
	string msg, str;
	object weapon;
	int myskill, k, l;
	float ap, ap2, dp, dp2, pp;
	int youcps, mycor, mystr, youstr;
	int damage_bonus, damage, wound;
	int delay;
	object ob;
	int cd = 8;
	weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	    if(!wizardp(me) && me->query("family/family_name")!="���ƶ�")
           return notify_fail("������������ֻ�л��ƶ����˲ſ����ã�\n");

	myskill=(int)me->query_skill("wuyue-spear",1);
	if(myskill<100)
		return notify_fail("��ģ�������ǹ�ݻ��������죡\n");
	myskill=(int)me->query_skill("pingtian-dafa",1);
	if( me->query("lunhui_zhuanshi") > 2 )
		cd = 5;
	else if( me->query("lunhui_zhuanshi") > 1 )
		cd = 6;
	else if( me->query("lunhui_zhuanshi") )
		cd = 7;
        if( time()-(int)me->query_temp("fengchan_end") < cd )
                return notify_fail("�����ö�Ͳ����ˣ�\n");

	if(myskill<100)
		return notify_fail("���ƽ��󷨵ȼ�����������ʹ����һ�У�\n");

	k=(int)me->query_skill("spear");
        if(k<140)
                return notify_fail("���ǹ�����𻹲�����ʹ����һ�л������ѣ�\n");
        l=(int)me->query_skill("literate",1);
	if((int)me->query("max_force") < 1000 )
                return notify_fail("����ڹ�̫�\n");

	if((int)me->query("force")<500)
		return notify_fail("������������ˡ�\n");

	me->set_temp("fengchan_end",time());
	mycor=me->query_cor();
	youcps=target->query_cps();
	ob=target->query_temp("weapon");

	ap = 0.0 + k;
	ap = (ap /12) * ap * ap;
	ap = ap + me->query("combat_exp");
	dp = 0.0 + target->query("combat_exp");
	ap2= COMBAT_D->skill_power(me, "spear", SKILL_USAGE_ATTACK);
	dp2 = COMBAT_D->skill_power(target,"dodge", SKILL_USAGE_DEFENSE);
	dp2=dp2/2;
	pp=COMBAT_D->skill_power(target,"parry", SKILL_USAGE_DEFENSE);
	pp=pp/2;
	if(objectp(ob)) pp=pp/2;
	mystr=me->query_str();//have force_factor
	youstr=target->query_str();
	damage_bonus = k;
	//damage_bonus=mystr*(damage_bonus+100+me->query("force_factor"))/100;
          damage_bonus=mystr+damage_bonus+me->query_temp("apply/damage")*2;
	//if( random(youcps) < 15 || random(ap+dp+ap2+dp2)>(dp+dp2)/2)
	//{
			msg = HIC "$N������"+ weapon->query("name")+ HIC"�ҳ�һʽ\n\n";
			msg +=HIC "������������\n";
			msg +=HIC "��������ک�\n";
			msg +=HIC "������������\nһ�ɺ�Ȼ����������$nȫ��\n";
			damage=calculate_damage(me, target, 120, damage_bonus);
			wound=random(damage-(int)target->query_temp("apply/armor"));
			if( (ap+dp+ap2+dp2)*random(1000000)/1000000>(dp+dp2) && damage > 0 )
			{
					target->receive_damage("kee", damage, me);
				  if(wound>0) target->receive_wound("kee", wound/2, me);
					str="�ұ�";
					if(objectp(ob)) str="���е�"+ob->query("name");
					msg += "$n����"+str+HIC"һ�ܣ�����ǹ�������������������֡�\n";
			}
			else msg += "����$p������$P����ͼ�����Խ����\n" NOR;

			msg += HIC"$Nǹ�ƶ�ת��"+ weapon->query("name")+ HIC"�����������ǵĺ�Х��$n��ȥ��\n\n" NOR;
			msg += HIB "˲������ǹ���ѵ���$n���ʺ�\n";
			//if(random(ap2+pp)>pp)
			//{
						msg +=HIB "   ������������\n";
						msg +=HIB "   ������������\n";
						msg +=HIB "   ������������\n��ʽ���绪ɽһ����ֱȡ$nҪ����\n";
						damage=calculate_damage(me, target, 140, damage_bonus);
						wound=random(damage-(int)target->query_temp("apply/armor"));
					if( (ap2+pp)*random(1000000)/1000000>pp && damage>0 )
					{
							target->receive_damage("kee", damage, me);
							if(wound>0) target->receive_wound("kee", wound/2, me);
							msg+=HIB"���$n�ʺ�һ�飬��㴭����������\n" NOR;
					}
			//}
			else msg+="�����$n���ɵ����ˡ�\n" NOR;
			msg += HIW "\n������$N��ת"+ weapon->query("name")+ HIW"β����$n�Ĵ��ȣ�\n";
			msg += "ͬʱ��Х��������Ϫ����������������";
			msg += "$n����˫�ۣ����Ҳ��С�\n" NOR;
							msg +=HIW "      ������������\n";
							msg +=HIW "      ���������ũ�\n";
							msg +=HIW "      ������������\n";
			//if(random(ap2+pp)>pp)
			//{
					damage=calculate_damage(me, target, 160, damage_bonus);
					wound=random(damage-(int)target->query_temp("apply/armor"));
					if( (ap2+pp)*random(1000000)/1000000>pp && damage>0 )
					{
							target->receive_damage("kee", damage, me);
							if(wound>0) target->receive_wound("kee", wound/2, me);
							msg +=HIW"��ʽ�������Σ����$n���Ȳ������������һ�����ӡ�\n" NOR;
					}
			//}
			else msg+="$n��׼���ƣ����������ˡ�\n" NOR;
			if( k>170 && l>140 )
			{
		      msg += HIM "\n$N����˳�����˴�"+ weapon->query("name")+ HIM"ײ��$n���·��紪�ޱʱ�ī��ֽ��";
		      msg += "��$n�ε����ѣ�\n" NOR;
		      msg +=HIM "         ������������\n";
					msg +=HIM "         �����º�婧\n";
					msg +=HIM "         ������������\n";
					msg +=HIM"��ʽ��á��紪�������ݺᡱ�����裡\n" NOR;
          damage=calculate_damage(me, target, 180, damage_bonus);
					wound=random(damage-(int)target->query_temp("apply/armor"));
          if( (ap2+pp)*random(1000000)/1000000>pp && damage>0 )
          {
          		target->receive_damage("kee", damage, me);
							if(wound>0) target->receive_wound("kee", wound/2, me);
              msg+=HIM"���$n�����Ժ�������ε���\n" NOR;
           }
           else msg+="���$nһ�����ģ�ȴûˤ����\n" NOR;
			  }
        if( k>240 && l>160 )
        {
        		msg += HIY "\n$Nǹ�����࣬"+ weapon->query("name")+ HIY"ƽƽ������ֱȡ��·����$n��";
            msg += "$n����������������Ȼ��֪���Ӧ����\n" NOR;
            msg +=HIY "            ������������\n";
						msg +=HIY "            ��ƽ����ӹ��\n";
						msg +=HIY "            ������������\n";
						msg +=HIY"��ʽ�������ң��ѻ���ǹ���ġ���ƽ��һʽ���ӵ�����ۣ�\n" NOR;
            damage=calculate_damage(me, target, 200, damage_bonus);
						wound=random(damage-(int)target->query_temp("apply/armor"));
            if( (ap2+pp)*random(1000000)/1000000>pp && damage>0 )
            {
            		target->receive_damage("kee", damage, me);
								if(wound>0) target->receive_wound("kee", wound/2, me);
                msg+=HIR"������ۣ�����һ����$n�ؿڱ��������������\n" NOR;
            }
            else msg+="���$nһ����������Ȼ�Ǳ���ȴ��ʵ�ã��ù���$N��һǹ��\n" NOR;
         }

         message_vision(msg, me, target);
// ����һ��������
// ap2+pp>pp
// ��Ч�ȼ�����300������ʶ�ִ���180
// 300���ֵ����297
// �����Ե����25
// ͬʱ���㣬���ʼ���΢С
         //if( wizardp(me) || ((ap2+pp)*random(1000000)/1000000>pp && k>300 && l>180 && random(300)>297 && random(me->query("kar"))>25) )
         if( wizardp(me) || (k>600 && l>400 && random(me->query("kar"))>30 && !random(5)) )
         {
         	damage=calculate_damage(me, target, damage_bonus, damage_bonus);
         	if(damage < 0)
         		damage = damage_bonus;
         	target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage/2, me);
                msg = HIG "\n$N����¶���־�֮ɫ��"+ weapon->query("name")+ HIG"��Ȼ����ʹ����" + 
                		"������ħ����һ�㣬\n��ǹ���Ѿ�����������֮�ʣ���������������ɱ����������Ծ��\n" NOR;
                msg +=HIG "               ������������������\n";
								msg +=HIG "               ��������������ɽ��\n";
								msg +=HIG "               ������������������\n";
								msg +=HIG"��ʽ�����ϵ���ʮ����ħ�������һ�У����ǹ������䣬��ض�ʱʧɫ��\n" NOR;
								msg+=HIG"��һʽ��������֮���������¡����š��ǻۡ���ӹ����һǹ��������֮�ؽ�$n�ݺ����飡\n" NOR;
								//me->start_call_out( (: call_other, __FILE__, "kill_him", me, target :), random(2)+4);
								message_vision(msg, me, target);
		if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) )  
		{
			str=me->name()+HIM"ʹ��"+HIY"��������ǹ��"+HIM+"ʧ���Ѿõľ���"+HIR"��������������ɽ��"+HIM+"��������֮����"+target->name()+HIM"��ɱ�ˣ�";
			message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
		}
	}
	msg+=COMBAT_D->report_status(target, "����");
	/*}
	else
	{
			msg += "����$p������$P����ͼ�����Խ����\n" NOR;
			message_vision(msg, me, target);
	}*/
  delay = random(2)+1;
	me->start_busy(delay);
	me->add("force", -300);

	return 1;
}

int calculate_damage(object me, object target, int base_damage, int damage_bonus)
{
	int damage;
	int myexp, youexp;

	damage=base_damage+(damage_bonus+random(damage_bonus))/2;
	myexp=me->query("combat_exp");
	youexp=target->query("combat_exp");
	if(random(youexp)>myexp*3/4) {
		damage-=damage/4;
		youexp/=2;
	}
	if (wizardp(me) && me->query("env/combat")=="verbose")
		tell_object(me, sprintf(HIC "damage: %d\n" NOR, damage));

	return damage;
}

void kill_him(object me, object target)
{
	string msg,str;
	if(me->is_fighting() && target->is_fighting() &&
	environment(me) == environment(target))
	{
		msg =HIR"\n$nֻ������ǰһ�����ʺ��ѱ��Դ�����������\n\nһ��Ѫ����ӿ��������$n���۾�������ͻ�˳�������\n" NOR;
                target->receive_damage("sen",target->query("max_sen")+1,me);
                target->receive_wound("sen", (int)target->query("max_sen")+1, me);
                target->receive_damage("kee",target->query("max_kee")+1,me);
                target->receive_wound("kee", (int)target->query("max_kee")+1, me);
                msg+=HIR"\n$N����$n��ʬ�壬�亹ֱð����\n" NOR;
                //COMBAT_D->report_status(target);

		message_vision(msg, me, target);
		str=me->name()+HIM"����"+HIY"��������ǹ��"+HIM+"ʧ���Ѿõľ���"+HIR"��������������ɽ��"+HIM+"����"+target->name()+HIM"��ɱ�ˣ�";
		message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
		target->heart_beat();
	}
	return ;
}
