#include <ansi.h>
inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
        string tmp;
        object ob = me;

        if( !arg )
                return notify_fail("��Ҫ��˭ȡʲô���֣�\n");

        if (sscanf(arg, "%s %s", tmp, arg) == 2)
                ob = find_player(tmp);
        if (!ob) return notify_fail("����û������ˡ�\n");

        if( strlen(arg) > 20 )
                return notify_fail("�������̫���ˣ���һ����һ��ġ�����һ��ġ�\n");
        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
        message_vision(HIY "$N��$n�����ָ�Ϊ" + arg + "��\n" NOR, me, ob);
        ob->set("name", arg);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: name [���] ����
 
�޸���һ��Լ������֡�

HELP );
        return 1;
}
