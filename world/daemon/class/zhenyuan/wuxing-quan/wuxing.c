/*�������������ԣ������С�
��ν�����ߣ���ľˮ������������֮�������ֻ����ܣ���ɴ�ǧ���硣
����ش󷨣�����������֮��������֮�������������֮˵��
��˼����ľ��ľ����������ˮ��ˮ�˻𡢻�˽�����������ˮ��ˮ��ľ��ľ���𡢻�������������
��������ħ���ض��ݴ�������ˡ��˴���Ҳ��
�������һ��ˮ����ˮ���̺����������ɿ�ˮ��ˮ��ɿ�����
�����������֮�ۣ������󽣶������и���֮��������ˣ����������������໯Ҳ��
��н��֮�������Էй�ˮ��Ȼ��н��֮�����ܷн���а���ǻ𲻿ɿ�ˮ���Ʋ����ӡ�
ˮ��������ڱ˴�֮�ƣ��Ʋ�������������������ʱ���κΣ�
Ω�б仯�ӡ���ǿ��֮�𣬵�����֮ˮ������ˮ��
�Ե���֮ˮ����У���ֲ��������ܻ���Ϊ����֮��������Կ�ˮ��
������֮�𣬵�ǿ��֮ˮ����ر��ˡ������ܻ���Ϊ����֮ˮ�������������
��������������ԣ���ǿ���������С�ľ��֮�����ȫ�޽�ˮ�������ԣ����������
��������������ʱ���ڱ仯֮�У�������Բ׺�Ϊɣ��Ҳ��
�����໯������������������ĳ�������֮�������ԣ������仯��˳Ӧʱ��Ҳ��
�������ѣ����޼�ǿ֮��������������֮���飬��Ȼ�޷��������Ϲ����������б仯�ߣ��������˶��ѡ�
�������໯������������֮�⡣����֮��ľˮ�����������Ϊ���㡯�������������䡯�������������ݡ�Ҳ��
�����㡢�������仯�����𡢰��������������Ϊ����֮������Ϊ����֮�ɡ�
*/
// wuxing.c  ����������˺�һΪ̫������̫�������޼����ڶ���
//����moon,kunlun,shushan
//��ľ��pansi,sanxian,fc
//��ˮ��xueshan,longgong
//�ϻ�putuo,hyd,hell
//������jjf,wdd,wzg
//��ˮľ���� ����
//��ľ��ˮ�� ���
#include <ansi.h>
inherit SSERVER;
mapping menpai = ([
		"�ݿ�ɽ�޵׶�"	:"��",
		"������"	:"��",
		"��ׯ��"	:"��",
		"���ƶ�"	:"��",
		"�Ϻ�����ɽ"	:"��",
		"���޵ظ�"	:"��",
		"��ѩɽ"	:"ˮ",
		"��������"	:"ˮ",
		"����ɽ���Ƕ�"	:"ľ",
		"��˿��"	:"ľ",
		"����ɢ��"	:"ľ",
		"�¹�"		:"��",
		"����ɽ���鶴"	:"��",
		"��ɽ��"	:"��"
	]);
mapping xiangke = ([
		"��":"��",
		"ľ":"��",
		"��":"ľ",
		"ˮ":"��",
		"��":"ˮ"
	]);
mapping xiangsh = ([
		"��":"ˮ",
		"ľ":"��",
		"��":"��",
		"ˮ":"ľ",
		"��":"��"
	]);
mapping color = ([
		"��":HIW"��"NOR,
		"ľ":HIC"ľ"NOR,
		"��":HIY"��"NOR,
		"ˮ":BLK"ˮ"NOR,
		"��":HIR"��"NOR
	]);
string *wuxing = ({"��","ľ","��","ˮ","��"});
int perform(object me, object target)
{
        string msg,f_name,str;
        int damage, ap, dp, i;
        int cd = 10;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��û�ж��ְ�����\n");
         if(!wizardp(me) && me->query("family/family_name") != "��ׯ��")
                return notify_fail("[����]����ׯ�۲���֮�ܣ�\n");
        if( !me->is_fighting(target) )
                return notify_fail("��Ҷ���æ��û����ʱ�俴����ݡ�\n");
        if (!me->query("wuxing_known"))
                return notify_fail("�㻹û���������е��ں���\n");
        if (me->query_skill("wuxing-quan",1)<200)
                return notify_fail("�������ȭ�������޷�������е��ں���\n");
        if (me->query_skill("unarmed",1)<200)
                return notify_fail("�����ȭ�Ų������޷��������е�������\n");
        if (me->query_skill("literate",1)<200)
                return notify_fail("��Ķ���ʶ�ֲ������޷�������е��ں���\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("����������������\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
	if( time() - (int)me->query_temp("wuxing_time") < cd )
                 return notify_fail("�����ö࣬�Ͳ����ˡ�\n");
        me->set_temp("wuxing_time",time());            
        ap = me->query_skill("wuxing-quan",1);    
        dp = me->query_skill("dodge",1);
        damage = me->query_skill("unarmed") + me->query("force_factor");
        damage = damage*2 + random(damage);
        damage = damage - target->query_temp("apply/armor");
        if( damage < (me->query_skill("unarmed",1) + me->query("force_factor")) ) 
        	damage = me->query_skill("unarmed") + me->query("force_factor");
 	f_name = target->query("family/family_name");
 	me->add("force",-damage/3);
 	if( me->query("wuxing_known") == 1 )
 	{
 		if( !f_name )
 		{
			damage = damage * 6 / 5 + random(damage/5);
 			str = wuxing[random(sizeof(wuxing))];
 			msg = HIM"\n$N��ת��������֮�����һȭ��һ��"+BLINK+ color[str] +HIM"����������$n��\n"NOR;
 		}
 		else
 		{
        		damage = damage * 5 / 4 + random(damage/4);
        		str = xiangke[menpai[f_name]];
        		if( !stringp(str) || str == "" || str == "0" )
        			str = wuxing[random(sizeof(wuxing))];
        		msg = HIM"\n$N����$n�������ԣ���ת����"+BLINK+color[str]+HIM"֮����ȫ�����һȭ��\n" NOR;
        	}
       	}
       	else if( me->query("wuxing_known") == 2 )
       	{
       		if( !f_name )
 		{
 			damage = damage * 4 / 3 + random(damage/3);
 			str = wuxing[random(sizeof(wuxing))];
 			msg = HIM"\n$N������������֮������"+BLINK+color[str]+HIM"֮������";
 			str = xiangsh[str];
 			msg =  msg +BLINK+ color[str] + HIM"֮�������������༤�����紺���������������ѣ�\n"NOR;
 			msg =  msg + HIB"$Nһ����Х���Ķ�ȫ����������$n���ش��һȭ��\n"NOR;
 		}
 		else
 		{
        		me->add("force",damage/5);
        		damage = damage * 3 / 2 + random(damage/2);
        		str = menpai[f_name];
        		if( !stringp(str) || str == "" || str == "0" )
        			str = wuxing[random(sizeof(wuxing))];
        		msg = HIM"\n$N��ת�����ķ�����$nʹ�õ�"+BLINK+color[str]+HIM"֮���������壬�����ķ���������\n"NOR;
        		for(i=0;i<3;i++)
        		{
        			str = xiangsh[str];
        			if(i==0) msg =  msg +"\n\t"+BLINK+ color[str] + HIM"֮��\n"NOR;
        			if(i==1) msg =  msg +"\n\t\t"+BLINK+ color[str] + HIM"֮��\n"NOR;
        			if(i==2) msg =  msg +"\n\t\t\t"+BLINK+ color[str] + HIM"֮��\n"NOR;
        		}
        		msg =  msg + HIM"�������������༤�����紺���������������ѣ�\n"NOR;
        		msg =  msg + HIB"$Nһ����Х���Ķ�ȫ����������$n���ش��һȭ��\n"NOR;
        	}
       	}
       	else
       	{
        	me->add("force",damage/4);
        	damage = damage * 2 + random(damage);
        	msg = HIW"\n$N��ת�����ķ����Ա���"+BLINK+HIY"��"+NOR+HIW"֮������"+BLINK+HIW"��"+BLK"ˮ"+HIC"ľ"+HIR"��"+NOR+HIW"�������С�\n"NOR;
        	msg =  msg + HIC"\n�������������༤�����������ֻ��������������������澭������\n"NOR;
        	msg =  msg + HIC"\n������������������Ρ����������ɶ��뾲��\n"NOR;
        	msg =  msg + HIY"\n��һ˲�䣬ԭ����Ҫ��ֹ������������ͬʱ����$N���������ء�\n"NOR;
        	msg =  msg + HIM"\n$N��$n�ݷ�����һ������ĺ����������ĵף�ɢ֮��أ�\n"NOR;
        	msg =  msg + HIM"\n$N������������һ�����磬�ᴩ�����������ؼ�ĺ�Ȼ����������������\n"NOR;
        	msg =  msg + HIM"\n$N���޼᲻�ݵĺ�Ȼ����������ȭͷ֮�ϣ��ӳ�һȭ��\n"NOR;
        	msg =  msg + RED"\n$n��$N����ѹ�Ĵ����������������ֳ��ֲ������飡\n"NOR;
       	}
       	message_vision(msg, me, target);
       	if( me->query("wuxing_known") <= 2 )
       	{
       		switch (str)
        	{
                       	case "��":
                       	{ 
                       		msg = target->name()+HIM"��"+me->name()+HIM"ʹ����ׯ�۾�ѧ��"+HIW+"̫��"+HIB+"����"+HIM"���е�"+BLINK+HIW"��"+NOR+HIM"֮��ɱ���ˣ�ʬ�����˿��������Ҳ��̶ã�";
                       		message_vision(WHT"\n$nֻ��һ�ɴ���ӭ������������������壡\n"NOR,me,target);
                               	break;
                       	}
	                case "ˮ": 
	                {
	                       	msg = target->name()+HIM"��"+me->name()+HIM"ʹ����ׯ�۾�ѧ��"+HIW+"̫��"+HIB+"����"+HIM"���е�"+BLINK+BLK"ˮ"+NOR+HIM"֮��ɱ���ˣ�ʬ��������飬������״��";
	                       	message_vision(CYN"\n$nֻ��һ�ɴ������Լ�����Χס����������󺣣��޷����㣡\n"NOR,me,target);
	                        break;
	                }
	                case "ľ":
                       	{ 
                       		msg = target->name()+HIM"��"+me->name()+HIM"ʹ����ׯ�۾�ѧ��"+HIW+"̫��"+HIB+"����"+HIM"���е�"+BLINK+HIC"ľ"+NOR+HIM"֮��ɱ���ˣ�ʬ�屻Ұ�����ǣ�����˻��ʣ�";
                       		message_vision(HIG"\n$nֻ��һ�ɴ���������˷�����������ֲ�����������ӣ�\n"NOR,me,target);
                               	break;
                       	}
                       	case "��":
                       	{ 
                       		msg = target->name()+HIM"��"+me->name()+HIM"ʹ����ׯ�۾�ѧ��"+HIW+"̫��"+HIB+"����"+HIM"���е�"+BLINK+HIR"��"+NOR+HIM"֮��ɱ���ˣ�ʬ�屻�յý��ڣ��ٱ治����ǰģ����";
                       		message_vision(RED"\n$nֻ��һ�ɻ�����������������յ��գ���Įǧ���������һ˿������\n"NOR,me,target);
                               	break;
                       	}
                       	case "��":
                       	{ 
                       		msg = target->name()+HIM"��"+me->name()+HIM"ʹ����ׯ�۾�ѧ��"+HIW+"̫��"+HIB+"����"+HIM"���е�"+BLINK+HIY"��"+NOR+HIM"֮��ɱ���ˣ�ʬ�����ѱ��������ǣ����޺ۼ���";
                       		message_vision(YEL"\n$nֻ��һ�ɴ����ӽ��´�ش�����һʱ��ض�ɽҡ����Ҳ�޷����㣡\n"NOR,me,target);
                               	break;
                       	} 
		}
       	}
       	else
       		msg = target->name()+HIM"��"+me->name()+HIM"ʹ����ׯ�۾�ѧ��"+HIW+"̫��"+HIB+"����"+HIM"��ɱ���ˣ���ʬ���Ͽ������κκۼ���";
       	if( random(ap+dp) > dp/(1+me->query("wuxing_known")) )
       	{
       		message_vision(HIR"\n$n��ʵ�޷��ֵ�����$N����ʵʵ���У����ۡ����³�һ����Ѫ���������˼��ص����ˣ�\n"NOR,me,target);
       		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
		if(wizardp(me)) tell_object(me,HIY"damage:"+ damage +"\n");
		COMBAT_D->report_status(target);
       	}
       	else
       	{
       		message_vision(HIB"\n$n����Ҫ��ס���Σ��������һ�����ģ�ȴ�պö����$N�ľ�����\n"NOR,me,target);
       	}
       	//��ʱ�����ţ����Ӹ�ҥ������
       	/*if( me->query("wuxing_known") > 2 && !userp(target) )
       	{
       		message_vision(HIW"\n$N����ͻȻ�ֳ�һ��̫��ͼ����$N��̤����������������У�\n"NOR,me,target);
       		message_vision(HIW"\n$N�����ɶ����ĺ�Ȼ����ת��Ϊ��������������˫���������̫��֮�У�\n"NOR,me,target);
       		message_vision(HIW"\n̫��ͼ�����������󣬶���һ��$N�������ɵ�$n���Ͽգ�����ʼ��ת��\n"NOR,me,target);
       		message_vision(HIW"\n̫��ͼԽתԽ�죬�������ֻʣ����һ����ڵ�С�㡣$N�������򣬶�̫�����е�����������һ�㣡\n"NOR,me,target);
       		message_vision(HIW"\n$nȴ������һ�����ܣ�̫��ͼ�д��������޾������������ݷ�Ҫ��$n��������һ�����磡\n"NOR,me,target);
       		message_vision(HIW"\n$n������ض��𣬱������գ�$Nֻ������ಡ���һ����$n�Ѿ���������̫��ͼ�У���̫��ͼͬʱ��ʧ�����ˣ�\n"NOR,me,target);
       		str=me->name()+HIM"ʹ����ׯ�۾�ѧ��"+HIW+"̫��"+HIB+"����"+HIM"����"+target->name()+HIM"��̫��ͼ�����������磬�����Ⱳ���ǻز����ˣ�";
		message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
       	}
       	else*/
       	//{
       		if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
        	{
			message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+msg+"\n"NOR,users());
		}	
       	//}
        return 1;
}
