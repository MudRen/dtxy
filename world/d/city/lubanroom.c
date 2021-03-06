inherit ROOM;
#include <ansi.h>
void create()
{
 set("short","班房");
        set("long", @LONG

这间不见天日的屋子是鲁班居住的, 因此叫班房. 不知为何,
后世将其引用为牢房之意. 虽然此屋深埋地下, 却也十分明亮
无数炼炉正在不停地为人们炼制兵器. 墙壁上还挂着一块牌子
(paizi), 好象写着什么.

LONG
        );
        set("exits", ([
                "up" : __DIR__"droproom",
        ]));
        set("objects",
        ([ //sizeof() == 1
               __DIR__"npc/luban" : 1,
        ]));
        set("no_fight", 1);
        set("no_magic", 1);
        set("item_desc", ([
                "paizi": @TEXT
可以使用的指令有:

register         注册装备。
deregister       注销装备。
fetch            取出注册的装备
list             查看注册的装备
payoff           付清保管费
luimprove        请鲁班帮你提升装备
selfimprove      自己动手提升装备
luembed          请鲁班帮你镶嵌宝石
selfembed        自己动手镶嵌宝石
upgrade          将装备升至下一等级

TEXT
        ]) );
        setup();
}