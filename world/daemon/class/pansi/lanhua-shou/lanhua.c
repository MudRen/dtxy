#include <ansi.h>

inherit SSERVER;
mapping xue_name = ([
	"xue_name1" : ({ HIR"�͹�Ѩ"NOR,HIR"����Ѩ"NOR,HIR"����Ѩ"NOR, }),
	"xue_name2" : ({ HIG"��ԪѨ"NOR,HIG"����Ѩ"NOR,HIG"�м�Ѩ"NOR, }),
	"xue_name3" : ({ HIY"�н�Ѩ"NOR,HIY"��ͻѨ"NOR,HIY"�ٻ�Ѩ"NOR, }),
	"xue_name4" : ({ HIM"����Ѩ"NOR,HIM"����Ѩ"NOR,HIM"���Ѩ"NOR, }),
	"xue_name5" : ({ HIW"�Ϲ�Ѩ"NOR,HIW"��ԨѨ"NOR,HIW"�쾮Ѩ"NOR, }),
	"xue_name6" : ({ HIC"��ȪѨ"NOR,HIC"����Ѩ"NOR,HIC"����Ѩ"NOR, }),
	"xue_name7" : ({ HIB"�İ�Ѩ"NOR,HIB"��ӭѨ"NOR,HIB"Ͽ��Ѩ"NOR, }),
	"xue_name8" : ({ WHT"����Ѩ"NOR,WHT"̫��Ѩ"NOR,WHT"�ػ�Ѩ"NOR, }),
	"xue_name9" : ({ CYN"�ٳ�Ѩ"NOR,CYN"�ٺ�Ѩ"NOR,CYN"����Ѩ"NOR, }),
]);
int perform(object me, object target)
{
        int damage,damage1,ap,dp;
        string msg,xuedao;

        int num,num_hit,i;
        int cd = 10;
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��û����ս����\n");
                
        if( (int)me->query_skill("lanhua-shou", 1) < 150 )
                return notify_fail("��������ֲ�����졣\n");

        if( (int)me->query_skill("jiuyin-xinjing", 1) < 150 )
                return notify_fail("��ľ����ľ�̫�͡�\n");

        if( (int)me->query("force") < 1000 )
                return notify_fail("������̫����\n");
	 if(!wizardp(me) && me->query("family/family_name")!="��˿��")
		return notify_fail("�㲻����˿�����ӣ��޷�����������\n");
	if( me->query("lunhui_zhuanshi") > 4 )
		cd = 6;
	else if( me->query("lunhui_zhuanshi") > 1 )
		cd = 8;
        if( time() - (int)me->query_temp("lanhua_time") < cd )
                 return notify_fail("���޷���������������\n");
        me->set_temp("lanhua_time",time());
        num = (me->query_skill("jiuyin-xinjing", 1) - 100)/50;
        num = num + random(num) + 1;
        ap = me->query("combat_exp")/10000;
        dp =  target->query("combat_exp")/10000;
        damage1 =  me->query_skill("unarmed")/2 + me->query_str() +random(me->query_skill("force")/4);
        if( num > 9 ) num = 9;
        msg = HIW "\n$N��̧���֣�����������������ָ���ۣ���һ�ᾹȻ����"+HIY+ chinese_number(num) +HIW"��⻪��Ȼ��"+BLINK+HIB"����"+NOR+HIW"��\n"NOR;
	msg = msg + HIC "\n$N΢΢һЦ��ָ���ᵯ"+BLINK+HIB"����"+NOR+HIC"��������Ļ��ߣ���������$n��\n"NOR;
	msg = msg + RED "\n$n���������䱸��ȴҲ���̴����"+BLINK+HIB"����"+NOR+RED"ʤ����\n"NOR;
	msg = msg + HIC "\n$N�����ָ��"+BLINK+HIB"����"+NOR+HIC"��Ȼ���٣�����$n����ҪѨ��\n"NOR;
	message_vision(msg, me, target);
	xuedao = "";
	for( i = 1 ; i <= num ; i++ )
	{
		if( random(ap) > dp/3 ) 
		{
			num_hit++;
			xuedao = xuedao + xue_name["xue_name" + i][random(3)] + " ";
		}
	}
	if( num_hit > 0 )
	{
		msg = HIR "\n$n��Ȼ�䱸�мӣ�ȴ���벻$N������˸�������æ���Ҽ䱻"+BLINK+HIB"����"+NOR+HIR"������\n"NOR;
		msg = msg + "\n\t\t" + xuedao + "\n\n"NOR;
		message_vision(msg, me, target);
		damage = damage1*num_hit;
		damage = damage - target->query_temp("apply/armor");
		if( damage < damage1 ) damage =  damage1;
		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
		COMBAT_D->report_status(target);
                me->add("force",-damage/5);
	}
	else
	{
		me->add("force",-100);	
		msg = HIG "\n$n��Ȼ�е���æ���ң��������Ƕ����$N���еĹ�����\n"NOR;
		message_vision(msg, me, target);
	}
        return 1;
}
