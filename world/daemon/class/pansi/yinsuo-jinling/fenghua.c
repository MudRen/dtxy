//��˿������pfm
//2004-1-6 by kryos //thank violet's describes  huarong 2004/1
//rewrited for dtxy2004 by huarong 2004/1
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit SSERVER;

int get_current_day_phase();
nosave mapping *day_phase = NATURE_D->query_day_phase();

int perform(object me, object target)
{
        string msg,kind,dodge_skill,str;
        int damage, qin,i,k,maxhit,myexp,youexp,ratio,skill;
        int chixinjian,qingxiajian,yinsuojinling,lanhuashou,jiuyinxinjing,pansidafa;
        int phase = get_current_day_phase();
        object weapon = me->query_temp("weapon");
        int cd = 10;
        //if(!wizardp(me))
        //	return notify_fail("��ʦ���ڲ���"+HIW+"���绪���衹"+NOR+"������\n");
      	if(!me->query("qingyun_known"))
           	return notify_fail("�㻹û��ѧ��"+HIW+"���绪���衹"+NOR+"������\n");
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail(HIW+"���绪���衹"+NOR+"ֻ����ս����ʹ�á�\n");

        if((int)me->query_skill("unarmed", 1) < 200 ||
           (int)me->query_skill("sword", 1) < 200 ||
           (int)me->query_skill("whip",1) < 200)
                return notify_fail("��Ļ�������ѧ�Ĳ����ң��޷�ʹ��"+HIW+"���绪���衹"+NOR+"!\n");

        if((int)me->query_skill("lanhua-shou", 1) < 200 ||
           (int)me->query_skill("qingxia-jian", 1) < 200 ||
           (int)me->query_skill("yinsuo-jinling",1) < 200||
           (int)me->query_skill("jiuyin-xinjing",1) < 200||
           (int)me->query_skill("pansi-dafa",1) < 200||
           (int)me->query_skill("chixin-jian",1) < 200)
                return notify_fail("����˿���Ĺ���ѧ�Ĳ����ң��޷�ʹ��"+HIW+"���绪���衹"+NOR+"!\n");

        if((int)me->query_skill("qin",1) < 200)
                return notify_fail("�㲻ͨ���ɣ��޷�ʹ��"+HIW+"���绪���衹"+NOR+"!\n");

        //if(weapon->query("id")!="yinsuo jinling")
        //        return notify_fail("�����������壬����û����˵ʲô����������������ͨѽ��");
        if(me->query("family/family_name")!="��˿��")
                return notify_fail(HIW"���绪���衹"+NOR+"ֻ����˿�����Ӳſ����ã�\n");
        if( (int)me->query("max_force") < 2000 )
                return notify_fail("���������Ϊ̫��������ʹ����"+HIW+"���绪���衹"+NOR+"��\n");
        if( (int)me->query("force") < 2000 )
                return notify_fail("�������������\n");
	if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("fenghua_end") < cd )
                return notify_fail("�����ö�Ͳ����ˣ�\n");

        qin = me->query_skill("qin",1);

        if(random(target->query_per())<=me->query("per") && (phase<0 || phase>5))
        {
                kind = CYN;
                msg = HIC"\n$N"+HIC+"�������Ľ��壬��������һ�䣺���쾻��筺���ǳ����²��ꡣ\n" NOR;
                msg = msg + HIC"���ٿ�������ʱ��������࣬�»��·�ҲԽ��ԽŨ�ˣ�\n"NOR;
                msg = msg + HIC"$n"+HIC+"���÷���˿�񣬼����������裬�»������վ������ı����ˡ�\n\n"NOR;
                msg = msg + HIC"$N"+HIC+"һ����Х��$n"+HIC+"��ǰ�»���ʢ�����������ֽţ�$N"+HIC+"չ����ǿ��Ĺ��ơ�\n\n"NOR;
                str = me->name() + HIM"ʹ����˿����ѧ" + HIC"���绪���衹"NOR + HIM"��" + target->name() + HIM"������" + HIC"��Ӱ�¡�"+HIM+"���⾳֮�У�ƮȻ��ȥ��";
        }
        else if(random(target->query_per())<=me->query("per") && phase>=0 && phase<=6)
        {
                kind = YEL;
                msg = HIY"\n$N"+HIY+"���Ż���Ľ��壬��������һ�䣺�������ѻ����ݣ��������¶��Ũ��\n" NOR;
                msg = msg + HIY"�趯�Ľ���ѭ�Ż���Ĺ켣�������⣬$N�����ν�����ʧ��һƬ���֮�У�\n"NOR;
                msg = msg + HIY"$n"+HIY+"�����ǽ����Ȼ����ȴ����Ŀ�����������ö�������ɱ�⽥����\n\n"NOR;
                msg = msg + HIY"$N"+HIY+"һ����Х��$n"+HIY+"��ǰ����ʢ�����������ֽţ�$N"+HIY+"չ����ǿ��Ĺ��ơ�\n\n"NOR;
                str = me->name() + HIM"ʹ����˿����ѧ" + HIY"���绪���衹"NOR + HIM"��" + target->name() + HIM"��" + HIY"�����⡹"+HIM+"���⾳֮��ƮȻ��ȥ��";
        }
        else
        {
                kind = BLU;
                msg = HIB"\n$N"+HIB+"�������˵Ľ��壬��������һ�䣺�������ճ����ҹ������˽��ʱ��\n"NOR;
                msg = msg + HIB"ɲ�Ǽ䣬��������ƾۺϣ���һ�������������ϸ�꣡\n"NOR;
                msg = msg + HIB"$n"+HIB+"ֻ��������ͻȻ����ɭȻ��ϸ������������ҹ��ԩ��Ѫ������ʱ���˼�����ս��\n\n"NOR;
                msg = msg + HIB"$N"+HIB+"һ����Х��$n"+HIB+"���ŵõ�ս�ľ���$N"+HIB+"չ����ǿ��Ĺ��ơ�\n\n"NOR;
                str = me->name() + HIM"ʹ����˿����ѧ" + HIB"���绪���衹"NOR + HIM"��" + target->name() + HIM"��" + HIB"�����꡹"+HIM+"���⾳֮�У����ŵû����ɢ��";
        }
        message_vision(msg, me, target);
	if(me->query("qingyun_known") == 1)
		qin = qin * 3 / 2;
	else
		qin = qin * 3;
	target->add_temp("apply/dodge",-qin/4);
	target->add_temp("apply/parry",-qin/4);
	me->add_temp("apply/attack",qin/4);
    	me->add_temp("apply/damage",qin/4);
      	message_vision(kind + BLINK + "���г�����\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "������ϼ��\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "�Ĺ�������\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "������˿��\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "�����ɴ˳�\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "���̽�����\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	message_vision(kind + BLINK + "�绪������\n" + NOR, me, target);
      	COMBAT_D->do_attack(me, target,weapon);
      	target->add_temp("apply/dodge",qin/4);
	target->add_temp("apply/parry",qin/4);
	me->add_temp("apply/attack",-qin/4);
    	me->add_temp("apply/damage",-qin/4);
    	me->start_busy(2);
    	me->set_temp("fenghua_end",time());
    	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )
		message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
        return 1;
}

int get_current_day_phase() {
    mixed *local = localtime(time()*60);
    int t = local[2] * 60 + local[1];
    int i;
    for (i=0; i<sizeof(day_phase); i++)
        if (t>=day_phase[i]["length"])
            t -= (int)day_phase[i]["length"];
        else
            break;
    return (i==0 ? sizeof(day_phase)-1 : i-1);
}
