//��������
//2006 ����
//2006 ���ӽ��ܹ���
 
#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

string *zui_miaoshu= ({
HIW"���Ƕ�Ů���Թ����ꡣ\n"+
HIR+"�����Ե�����ϸ�� ������������ת��$N"+HIR+"��֪�����յ���Ӱ�졣\n"NOR,
HIB"��Ȼ����������ʿ���г���\n"+
HIR+"ɲ�Ǽ䣬������ü����߿������ư��磬������׳�����ְ�$N"+HIR+"������һ����ȫ��ͬ�ľ��硣\n"NOR,
HIM"���������޸��٣������Զ�η��\n"+
HIR+"������ת�����滺����������ǰ�����Ȼ�ڱ̿գ�$N"+HIR+"��Ȼ�������Լ�����ս���С�\n"NOR,
HIY"��౰���Ⱥ�������·�ˡ�\n"+
HIR+"��Ȼ��$N"+HIR+"�����ƺ���һֻ�߹�ķ����������������г�͡�������\n"NOR,
HIG"���ʷִ粻���ϣ�ʧ��һ��ǧ��ǿ��\n"+
HIR+"$N"+HIR+"�лк����������ͱ���һ��һ��������յĸ߷��ʵǡ�\n"NOR,
});

string *shoufa_msg = ({"Ĩ","��","��","��","Ʋ","��","��","��"});
string *yun_msg = ({"��","��","��","��","��"});

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;
        
        if(me->query_temp("BAIFA_perform")) 
                return notify_fail("���Ѿ�ʹ�����������ϡ��ˣ�\n");
        if( time()-(int)me->query_temp("BAIFA_end") < 10 )
                return notify_fail("�����ö�Ͳ����ˣ�\n");
        
        if((int)me->query("max_force") <1000 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 1000 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") <500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("chixin-jian",1) <120)
                return notify_fail("��ĳ��Ľ����𻹲���ʩչ��һ����������!!\n");
        if((int)me->query_skill("yueying-wubu",1) <120)
                return notify_fail("�����Ӱ�貽�ȼ�����!!\n");
        if((int)me->query_skill("qin",1) <120)
                return notify_fail("������յȼ�����!!\n");
        if (!present("wuxian qin", me) && !me->is_manmade_npc())
                return notify_fail("���������ϡ�����������ϲ���ʹ�á�\n");
        if(!wizardp(me) && me->query("family/family_name") != "��˿��" )
                return notify_fail("�㲻����˿������,������������!!\n");
        
        weapon=me->query_temp("weapon");
        if(me->is_fighting())
        {
        	target = offensive_target(me);
     		msg = HIM  "$N���ֳֽ�Ӧ�У�����ȡ�ٻ��������Ღ�����ң�����������ʧ���Ѿõľ�ѧ����";
     		msg = msg + "\n"YEL"             ������"HIC"���ϡ�";
		msg = msg + "\n"HIW"����ֻ��$N�ٽ���һ�����콣�������뵰����$n��\n\n" NOR;
    		message_vision(msg, me,target);
     	}
     	else
     	{
     		msg = HIM  "$N��ϥ���ڵ��ϣ����ֳֽ������ָ��٣����ᵯ��������ʧ���Ѿõľ�ѧ";
     		msg = msg + YEL"������"HIC"���ϡ�"+HIM"������\n"NOR;
		message_vision(msg, me);
	}
        skill = me->query_skill("qin",1);
        me->set_temp("BAIFA_perform", 1);
        call_out("checking", 2, me);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill);
        me->add("force", -200);
        return 1;
}
void checking(object me)
{

	object weapon,target;
	int damage,flag = 0;
	string str;
	weapon = me->query_temp("weapon");
	
        if( me->query_temp("BAIFA_perform")  ) 
        {
           	if (!present("wuxian qin", me) && !me->is_manmade_npc() ) 
           	{
                	tell_object(me, "\n����ٶ��ˣ��޷��������࣡\n" NOR);
                	me->delete_temp("BAIFA_perform");
			me->set_temp("BAIFA_end",time());
                	return;
           	}
           	else if ( (int)me->query("force") < 1000  ) 
           	{
                	tell_object(me, "\n���������̲��㣬���Գ������������ϡ���������\n" );
			me->delete_temp("BAIFA_perform");
			me->set_temp("BAIFA_end",time());
                	return;
           	}
           	else if ( (int)me->query("sen") < 500  ) 
           	{
                	tell_object(me, "\n��ľ���̫��޷��������࣡\n" );
			me->delete_temp("BAIFA_perform");
			me->set_temp("BAIFA_end",time());
                	return;
           	}
	   	else 
	   	{
	   		//if( me->is_fighting() && me->query("qingyun_known") )
	   		if( me->is_fighting() )
	   		{
	   			target = offensive_target(me);
	   			if( objectp(target) && present(target->query("id"), environment(me)) )
	   			{
	   				/*message_vision(HIM"\n$N��"+shoufa_msg[random(sizeof(shoufa_msg))]+"���ң����������бų�һ�������"+yun_msg[random(sizeof(yun_msg))]+"����\n"NOR, me,target);
	   				if( random(me->query_skill("qin",1)) > target->query_skill("force",1)/3 )//��һ�Σ��˺���Ѫ
	   				{
	   					message_vision(HIR"$Nһ�������������������˻���������\n"NOR, target);
	   					damage = me->query_skill("qin",1)+random(me->query_skill("jiuyin-xinjing",1))-random(target->query_skill("force",1));
	   					if( damage < 1 ) damage = 1+random(me->query_skill("qin",1))/3;
	   					target->receive_damage("kee",damage,me);
	   					target->receive_wound("kee",damage/2,me);
	   					me->add("force",-damage/10);
	   					COMBAT_D->report_status(target);
	   					flag = 1;
	   				}
	   				if( random(me->query_skill("qin",1)) > target->query_skill("spells",1)/3 && me->query("qingyun_known") > 1 )//�ڶ��Σ��˺�����
	   				{
	   					if( !target->is_busy() ) target->start_busy(random(2));
	   					message_vision(HIR"���������$Nֻ���ö�Ĥ�类��̣�ͷ�����ѣ�\n"NOR, target);
	   					damage = me->query_skill("qin",1)+random(me->query_skill("pansi-dafa",1))-random(target->query_skill("spells",1));
	   					if( damage < 1 ) damage = 1+random(me->query_skill("qin",1))/3;
	   					target->receive_wound("sen",damage,me);
	   					me->add("force",-damage/10);
	   					COMBAT_D->report_sen_status(target);
	   					flag = 1;
	   				}
	   				if( !flag )
	   					message_vision(YEL"$N��Ϊ��񣬾�Ȼ�����������ţ�����\n"NOR, target);
	   				*/
	   				message_vision(zui_miaoshu[random(sizeof(zui_miaoshu))], target, me);
	   				if( random(me->query_skill("qin",1)) > target->query_skill("spells",1)/3 )
	   				{
	   					message_vision(HIR"���������$N���������侳����֪����������˼����\n"NOR, target);
		   				damage = me->query_skill("qin",1)+random(me->query_skill("pansi-dafa",1))-random(target->query_skill("spells",1));
		   				if( damage < 1 ) damage = 1+random(me->query_skill("qin",1))/3;
		   				target->receive_wound("sen",damage,me);
		   				me->add("force",-damage/10);
		   				COMBAT_D->report_sen_status(target);
				   		if( (target->query("eff_sen") < 0 || !living(target)) && !random(5) )  
					        {
							str=target->name()+HIM"��"+me->name()+HIM+"�����"+NOR+HIW+"��ʴ������"+HIM+"�����ˣ�"NOR;
                         				message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
						}
	   				}
	   				else
	   					message_vision(YEL"$N��Ϊ��񣬾�Ȼ�����������ţ�����\n"NOR, target);
	   			}
	   		}
	   		call_out("checking", 2+random(2), me, target);
	   	}
	}
	else return;
}  



void remove_effect(object me)
{       
	if ( me->query_temp("BAIFA_perform") ) {
        message_vision(HIC"$N��һ�ӣ�ָ�����Ử�����ң������������ˣ��������ؼ�ֻ���������ϡ�\n"NOR, me);
        me->delete_temp("BAIFA_perform");
        me->set_temp("BAIFA_end",time());
         }
}
