// by gslxz@mhsj 1/7/2001
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string banghui;
	object ob;
	object lp;
	if(! me->query("banghui"))
		return notify_fail("ֻ�а��İ�������ʹ������ָ�\n");
	banghui=me->query("banghui");
	if(me->is_fighting()||me->is_busy())
		return notify_fail("����æ���ء�\n");
	if(! arg)
		return notify_fail("��Ҫ��λ��˭��\n");
	if( me->query("id")==arg)
		return notify_fail("��λ���Լ����б�Ҫ��\n");
	if(! ob=present(arg,environment(me)))
		return notify_fail("���û����ô����ҡ�\n");
	if(! userp(ob))
		return notify_fail("��ֻ����λ����ҡ�\n");
	if( ob->query("banghui")!=banghui)
		return notify_fail("��ֻ����λ����������ҡ�\n");
	if(ob->is_fighting()||ob->is_busy())
		return notify_fail("�Է���æ���ء�\n");
	lp=new("/obj/lingpai");
	lp->create(banghui);
	if( lp->query("no_use"))	{
		destruct(lp);
		return notify_fail("��İ���ļ������⣬������ʦ��ϵ��\n");
	}
	if(lp->query("bangzhu_id")!=me->query("id"))	{
		destruct(lp);
		return notify_fail("�㲻�ǰ��������޷�ʹ������ָ�\n");
	}
// by gslxz@mhsj 1/7/2001
	lp->set("bangzhu",ob->query("name"));
	lp->set("bangzhu_id",ob->query("id"));
	lp->save();
	destruct(lp);
	message_vision("$N����ᡸ"+banghui+"���İ���֮λ��λ����$n��\n",me,ob);
	ob->set("title",YEL+ob->query("banghui")+"����"NOR);
	me->set("title",HIG+ob->query("banghui")+"����"NOR);
       return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ��rangwei <ĳ��>
���ָ��Ϊ����ר�ã�����������֮λ��λ�����ˡ�
ǰ����ĳ�˱���Ϊ������ڡ�
HELP
        );
        return 1;
}
