//lestat for ����ɽ
//2001 ������

#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill, ktzskill, ktz_add;  // emotion
	int cd = 6;
        string msg,str;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�������ơ�?\n");
//        if(me->query_temp("BAIGU_perform"))
//                return notify_fail("���Ѿ�ʹ���������ơ��ˣ�\n");
	
	if( me->query("lunhui_zhuanshi") > 3 )
		cd = 4;
	else if( me->query("lunhui_zhuanshi") > 1 )
		cd = 5;
        if( time()-(int)me->query_temp("BAIGU_end") < cd )
                return notify_fail("�����ö�Ͳ����ˣ�\n");
// emotion        if( me->query_temp("pfmxue") )
// emotion                return notify_fail("������ȫ������������ѩ��\n");

        if(!me->is_fighting(target) )
                return notify_fail("������ֻ����ս����ʹ��!!\n");

        if((int)me->query("max_force") <1000 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") <50 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("kaitian-zhang",1) <100)
                return notify_fail("��Ļ�Ԫ�����Ƽ��𻹲���ʩչ��һ��������!!\n");
        if((int)me->query_skill("unarmed",1) <100)
                return notify_fail("��ĸ��˻�֮���ȼ�����!!\n");
        if(me->query("family/family_name") != "����ɽ���鶴" && !me->is_manmade_npc() )  // emotion
                return notify_fail("����������Ե,���򲻵��Ʒ��ľ���!!\n");

        me->delete("env/brief_message");
        target->delete("env/brief_message");
        weapon=me->query_temp("weapon");
     msg = HIC
"\n$NĬ�������ķ���ͻȻ˫�Ʊ�צ��ʹ�������ƾ�ѧ"HIR"�������ơ�"HIC"���������࣬����һƬצӰ�Ӱ���б���$n!\n" NOR;
    message_vision(msg, me, target);

        skill = me->query_skill("unarmed");
        ktzskill = me->query_skill("kaitian-zhang",1);  // emotion
// 		add_temp("apply/attack", ( skill + ktzskill ) * 4);  // emotion
//        me->set_temp("BAIGU_perform", 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
//        add_temp("apply/attack", -( skill + ktzskill ) );  // emotion
//        me->delete_temp("BAIGU_perform");
        me->set_temp("BAIGU_end",time());
            if ( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )
                       {str=target->name()+HIM"��"+me->name()+"�������ش�"NOR+HIR"�������ơ�"+HIM"ץ���ˣ�";
	                 message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	               }
        me->add("force", -200);
        return 1;
}

