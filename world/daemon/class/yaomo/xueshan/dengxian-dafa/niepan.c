// �������
//lestat for ѩɽ

#include <ansi.h>

int cast(object me, object target)
{
        int mymana=me->query("mana"), cost=100, cure;
	int jin, qi, neili, fali, shiwu, yinshui;
	int delay;
	string msg;

	if(me->is_busy())
		return notify_fail("����æ���أ������������ɣ�\n");
        if( time()-(int)me->query_temp("niepan_end") < 60 )
          return notify_fail("���ԡ�������ˣ�\n");
      if(me->query("family/family_name") != "��ѩɽ"
      || me->query_skill("dengxian-dafa", 1) < 100)
              return notify_fail("�㲻�Ƿ��ݣ��޷�ԡ��������\n");
      if(!me->is_fighting())
          return notify_fail("�������ֻ����ս����ʹ�ã�\n");
        if( mymana < cost*2 )
                return notify_fail("��ķ���������\n");

//        if (cost<mymana/2) cost=mymana/2-1;
        if (cost<mymana/10) cost=mymana/10-1;

        if( (int)me->query("eff_kee") < (int)me->query("max_kee") / 2 )

		cost=cost/2;
		message_vision(BLU"\n$N��ɫ�ҵ������ִ򿪷��٣������´����������ϣ����ŵ�ȼ���׷ۣ�ҧ����⣬һ��"RED"��Ѫ"BLU"����������������죬��������𻨣�"HIR"��"BLU"����һ�����漴��Ϊ������\n"NOR,me,target);
		message_vision(HIW"\n��ʱ$N�������ް��Ѫɫ��һ�ڿ���Ѫ��ס��"RED"����"WHT"����ȥ ������Խ��Խ��!!\n"NOR,me,target);
		message_vision(HIR"\n�漴��$N���˼����䡣�͵����Ӽ����������ݰ���ת��ʮ���Ȧ�ӣ����Ŵ����������������Ѷ��ز������ȼ�գ�����һ��"RED"��ǽ"HIR"�㣬������ɽ����֮�ƽ�$N��û��\n"NOR,me,target);
		message_vision(HIR"\n����һ��������һֻ"HIY"�ʷ�"HIR"�ӻ����г������һƬƬ��ë�ӿ���ѩ����Ʈ�䣬$N�������£�ȫ�����»�Ȼһ�£�\n"NOR,me,target);
		delay = random(8-me->query_kar()/5);
		if( delay > 0 ) me->start_busy(delay);

        me->add("mana", -cost);
        jin = me->query("max_sen");
        qi =me->query("max_kee");
        fali = me->query("max_mana");
        neili = me->query("max_force");
        shiwu = me->max_food_capacity();
        yinshui = me->max_water_capacity();
        me->set("eff_sen", jin);
        me->set("eff_kee", qi);
        me->set("sen", jin);
        me->set("kee", qi);
//        me->set("mana", fali);
//        me->set("force", neili);
        me->set("force", neili*2);
        me->set("food", shiwu);
        me->set("water", yinshui);
	me->set_temp("niepan_end",time());
        return 1;
}
