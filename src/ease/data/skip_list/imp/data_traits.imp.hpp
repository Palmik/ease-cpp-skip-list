template < typename K
         , typename V
         , typename C = std::less<const K>
         , typename A = std::allocator<K>
         , u8 LEVEL_MAX = 32
         , u8 LEVEL_PRO_INVERSE = 4
         >
struct skip_list_traits_base
{
    static const u8 level_max = LEVEL_MAX;
    static const u8 level_pro_inverse = LEVEL_PRO_INVERSE;

    static u8 random_level(u8)
    {
        // Better randomness, but much slower.
        //static std::random_device rd;
        //static std::mt19937 gen(rd());
        //static std::geometric_distribution<> distribution
        //  ( 1.0 / static_cast<double>(LEVEL_PRO_INVERSE)
        //  );
        //
        //return std::min(1 + static_cast<u8>(distribution(gen)), LEVEL_MAX);
       
        u8 lvl = 1;
        while ((random()&0xFFFF) < (0xFFFF / LEVEL_PRO_INVERSE))
        {
            ++lvl;
        }
        
        return (lvl < LEVEL_MAX) ? lvl : LEVEL_MAX;
    }
};

