-- Maths VERSION: 1.8.130828

-- usage:

-- Vectors:
-- local vector = Vector(); or Vector(x,y,z) or Vector( { x,y,z) })
-- local print(vector) -- "x: x  y: y  z: z"
-- vector:SetX( x ) or SetY or SetZ
-- vector:Set( x ,y , z) -- sets the value
-- vector:X(), Y(), Z() -- returns the value
-- vector:Normalize() -- normalizes the vector passed and returns it
-- vector() -- returns x,y,z
-- vector:Magnitude() or Length()
-- Vector.DotProduct( vector , othervector) or ScalarProduct or InnerProduct
-- Vector.AngleBetween( vector, othervector )

-- Quaternions:
-- local q = Quaternion() or Quaternion( x,y,z, w) or Quaternion( {x,y,z,w} )

-- don't make more than 1 copy of this
if MATHS then
   return
end

-- ROUNDING!!!

local ceil = math.ceil;
local floor = math.floor;

function math.round(num, idp)
    local mult = 10^(idp or 0)
    if num >= 0 then return floor(num * mult + 0.5) / mult
    else return ceil(num * mult - 0.5) / mult end
end

-- faster math
local round = math.round;
local sqrt = math.sqrt;
local sin = math.sin;
local cos = math.cos;
local acos = math.acos;

-- faster globals
local type = type;
local getmetatable = getmetatable;
local setmetatable = setmetatable;
local print = print;
------------------------------------------------
------------------------------------------------
-------------      VECTORS     -----------------
------------------------------------------------
------------------------------------------------

Vector = {}
local Vector = Vector;
local X = 1;
local Y = 2;
local Z = 3;
Vector.__index = Vector;

-- Vector()
-- Vector( x,y,z )
-- Vector( {x,y,z} )
-- Vector( vector )
setmetatable(Vector, {
   __call = function( self, x,y,z)
        local new = {0,0,0}
        setmetatable(new, Vector);
        new:Set(x,y,z)
      return new;
   end
})

Vector.__add = function(a,b)

   if type(a) == "number" then
      a = {a,a,a}
   elseif type(b) == "number" then
      b = {b,b,b}
   end

   return setmetatable( {
      a[X] + b[X],
      a[Y] + b[Y],
      a[Z] + b[Z]
   }, Vector )
end

Vector.__sub = function(a,b)
   if type(a) == "number" then
      a = {a,a,a}
   elseif type(b) == "number" then
      b = {b,b,b}
   end

   return setmetatable( {
      a[X] - b[X],
      a[Y] - b[Y],
      a[Z] - b[Z]
   }, Vector )
end

Vector.__mul = function(a,b)
   if type(a) == "number" then
      a = {a,a,a}
   elseif type(b) == "number" then
      b = {b,b,b}
   end

   return setmetatable( {
      a[X] * b[X],
      a[Y] * b[Y],
      a[Z] * b[Z]
   }, Vector )
end

Vector.__div = function(a,b)
   error("Division not implemented")
   -- why would I need this?
end

Vector.__call = function(self)
   return self[X],self[Y],self[Z];
end

local p = 0.00000000001;
local d;
Vector.__eq = function(a,b)
   for i=1,3 do
      d = a[i] - b[i]
      if d > p or d < -p then
         return false;
      end
   end
      return true;
end


function Vector:SetX( n )
   if type(n) == "number" then
      self[X] = n;
   end
end
function Vector:SetY( n )
   if type(n) == "number" then
      self[Y] = n;
   end
end
function Vector:SetZ( n )
   if type(n) == "number" then
      self[Z] = n;
   end
end

function Vector:X()
   return self[X];
end
function Vector:Y()
   return self[Y];
end
function Vector:Z()
   return self[Z];
end

function Vector:Set( x, y, z )
    self[X] = x;
    self[Y] = x;
    self[Z] = z;
end

function Vector:Normalize()
   local x = self[X];
   local y = self[Y];
   local z = self[Z];

   local magnitude = self:Length();
    self[X] = x/magnitude;
    self[Y] = y/magnitude;
    self[Z] = z/magnitude;

   return self;
end



function Vector:Magnitude()
   local x = self[X];
   local y = self[Y];
   local z = self[Z];
   return sqrt(x*x + y*y + z*z);
end
Vector.Length = Vector.Magnitude;

function Vector:MagnitudeSquared()
   local x = self[X];
   local y = self[Y];
   local z = self[Z];
   return x*x + y*y + z*z;
end
Vector.LengthSquared = Vector.MagnitudeSquared;

function Vector.DotProduct(a,b)
   return ( a[X] * b[X] ) + ( a[Y] * b[Y] ) + ( a[Z] * b[Z] );
end
Vector.InnerProduct = Vector.DotProduct;
Vector.ScalarProduct = Vector.DotProduct;

function Vector.AngleBetween( a, b)
   local dot = Vector.DotProduct(a,b);
   return acos( dot / ( a:Magnitude() * b:Magnitude() ) );
end

function Vector:New()
end

function Vector:ToString()
   return string.format("x: %+7.7f  y: %+7.7f  z: %+7.7f",
   self[X], self[Y], self[Z] );
end

Vector.__tostring = Vector.ToString





------------------------------------------------
------------------------------------------------
-------------     QUATERNIONS  -----------------
------------------------------------------------
------------------------------------------------

-- use the variables below to access the necessary data;
-- also W == SCALAR
Quaternion = {}
-- component indexes

local W = 1;
local X = 2;
local Y = 3;
local Z = 4;

local SCALAR = W;
Quaternion.__index = Quaternion;
Quaternion.__call = function(self)
   return self[W], self[X], self[Y], self[Z];
end


 -- Quaternion();
 -- Quaternion(x,y,z,w);
 -- Quaternion( Vector, w)
 -- Quaternion( quaternion );
setmetatable(Quaternion, {
   __call = function(self, w, x,y,z)
      return setmetatable({w,x,y,z}, Quaternion);
   end
})


Quaternion.__mul = function(a,b)

   -- q = a * b
   local aw = a[W];
   local ax = a[X];
   local ay = a[Y]
   local az = a[Z];

   local bw = b[W];
   local bx = b[X];
   local by = b[Y];
   local bz = b[Z];

   return setmetatable( {
      (aw * bx + ax * bw + ay * bz - az * by),
      (aw * by - ax * bz + ay * bw + az * bx),
      (aw * bz + ax * by - ay * bx + az * bw),
      (aw * bw - ax * bx - ay * by - az * bz)
   }, Quaternion)

end

-- really this could use a few tweaks
-- negatives can be the same rotation
-- (different paths)
local p = 0.00000000001;
local d;
Quaternion.__eq = function(a,b)
   for i=1,4 do
      d = a[i] - b[i]
      if d > p or d < -p then
         return false;
      end
   end
      return true;
end



function Quaternion:Magnitude()
   local w = self[W];
   local x = self[X];
   local y = self[Y];
   local z = self[Z];
   return sqrt(w*w + x*x + y*y + z*z);
end
Quaternion.Length = Quaternion.Magnitude;
Quaternion.Norm = Quaternion.Magnitude;

function Quaternion:Normalize()
   local w = self[W];
   local x = self[X];
   local y = self[Y];
   local z = self[Z];
   local magnitude = sqrt(w*w + x*x + y*y + z*z);
   if magnitude ~= 0 then
        self[W] = w/magnitude;
        self[X] = x/magnitude;
        self[Y] = y/magnitude;
        self[Z] = z/magnitude;
   end
   return self;
end



function Quaternion:New(...)
    local new;
    if select("#", ...) > 0 then
        new = {...};
    else
        new = {1, 0, 0, 0};
    end;
   setmetatable(new,self)
   return new;
end

function Quaternion:SetX( n )
   if type(n) == "number" then
      self[X] = n;
   end
end
function Quaternion:SetY( n )
   if type(n) == "number" then
      self[Y] = n;
   end
end
function Quaternion:SetZ( n )
   if type(n) == "number" then
      self[Z] = n;
   end
end
function Quaternion:SetScalar( n )
   if type(n) == "number" then
      self[W] = n;
   end
end
function Quaternion:SetW(n)
   if type(n) == "number" then
      self[W] = n;
   end
end


function Quaternion:X()
   return self[X];
end
function Quaternion:Y()
   return self[Y];
end
function Quaternion:Z()
   return self[Z];
end
function Quaternion:Scalar()
   return self[W];
end
function Quaternion:W()
   return self[W];
end

function Quaternion:Set( w, x, y, z)
   self:SetScalar( w );
   self:SetX( x );
   self:SetY( y );
   self:SetZ( z );
end




function Quaternion:Conjugate()
   local conjugate = Quaternion(
      self[W],
      -self[X],
      -self[Y],
      -self[Z]
    )
   return conjugate;
end

function Quaternion:Inverse()
   -- actual inverse is q:Conjugate() / (math.abs(q:Magnitude) ^ 2)
   -- but as we only deal with unit quaternions we can just force a normalization
   -- q:Conjugate() / 1 == q:Conjugate();

   self:Normalize();
   return self:Conjugate();

end


function Quaternion:ToAxisAndAngle()
      local w = self[W];
      local x = self[X];
      local y = self[Y];
      local z = self[Z];
    if w > 1 then
        self:Normalize();
    end

    local angle = 2 * acos( w )
    local s = sqrt( 1 - w*w );

    if s > .001 then
        x = x / s;
        y = x / s;
        z = x / s;
    end
    return Vector(x,y,z), angle

end
local axis = Vector();
function Quaternion:FromAxisAndAngle( x,y,z, angle)
   if getmetatable(self) ~= Quaternion then
      -- want a generic quaternion
      angle = z;
      z = y;
      y = x;
      x = self;
      self = setmetatable({0,0,0,1}, Quaternion)
   end

   if type(x) == "table" then
      -- passed as ({vector}, angle)
      -- creates or copies the vector or Vector
      axis[X] = x[X];
      axis[Y] = x[Y];
      axis[Z] = x[Z];

         angle = y;

   elseif angle then
      -- passed as ( x, y, z, angle) -- (rough check)
      axis[X] = x;
      axis[Y] = y;
      axis[Z] = z;
   else
      error("Quaternion.FromAxisAndAngle needs and angle")
   end

   axis:Normalize();
   angle = angle / 2 ;
   local sinangle = sin(angle);
   -- accessing an vector by [X] will not be correct
   self[X] = ( axis[X] * sinangle );
   self[Y] = ( axis[Y] * sinangle );
   self[Z] = ( axis[Z] * sinangle );
   self[W] = ( cos(angle) );

   return self;

end



function Quaternion.DotProduct( a, b )
   return ( a[X] * b[X] ) + ( a[Y] * b[Y] ) + ( a[Z] * b[Z] ) + ( a[W] * b[W] );
end
Quaternion.ScalarProduct = Quaternion.DotProduct;
Quaternion.InnerProduct = Quaternion.DotProduct;


-- v' = qr * v * qr-1
-- vector3 = (q * quaternion( vector, 0 ) * q:conjugate() ).Vector();
-- this is one of the most heavily used and slowest functions
-- so its been optimized to hell and back
-- a more normal, and decently optimized version is found next
-- this version is about 2x faster than RotatedVector2
local q = Quaternion();
function Quaternion:RotatedVector( x, y, z )
    if not z then
        -- x = {x,y,z}
        z = x[3];
        y = x[2];
        x = x[1]; -- and now we overwrite
    end

    local a = { -- vector to quat
        x,
        y,
        z,
        0
    }
    local b = { -- conjugate
        -self[X],
        -self[Y],
        -self[Z],
         self[W],
    }

    -- local r = self * v * conjugate;
    -- local q = v * c;
    local aw = 0;
    local ax = a[X];
    local ay = a[Y]
    local az = a[Z];

    local bw = b[W];
    local bx = b[X];
    local by = b[Y];
    local bz = b[Z];
    -- removed all the mults by aw, which would result in 0;

    q[X]   =  ax * bw + ay * bz - az * by;
    q[Y]   = -ax * bz + ay * bw + az * bx;
    q[Z]   =  ax * by - ay * bx + az * bw;
    q[W]   = -ax * bx - ay * by - az * bz;
    --[[
    local q = {
        (aw * bx + ax * bw + ay * bz - az * by),
        (aw * by - ax * bz + ay * bw + az * bx),
        (aw * bz + ax * by - ay * bx + az * bw),
        (aw * bw - ax * bx - ay * by - az * bz)
    }
    -- ]]

    -- local r = self * q;

    local a = self;
    local b = q;
    aw = a[W];
    ax = a[X];
    ay = a[Y]
    az = a[Z];

    bw = b[W];
    bx = b[X];
    by = b[Y];
    bz = b[Z];

    -- and we strip the w component from this
    -- which makes it a vector
    local q = {
        (aw * bx + ax * bw + ay * bz - az * by),
        (aw * by - ax * bz + ay * bw + az * bx),
        (aw * bz + ax * by - ay * bx + az * bw),
    }

      return setmetatable(q, Vector);
end

-- this is a decently optimized version; about twice as slow as version 1
function Quaternion:RotatedVector2( x, y, z )
      if not z then
         -- {x,y,z}
         x = x[1];
         y = y[2];
         z = z[3];
      end
      local conjugate = self:Conjugate();
      local v = Quaternion(x, y, z, 0);
      local r = self * v * conjugate;
      return setmetatable( {r[X], r[Y], r[Z]}, Vector );
end

function Quaternion:ToString()
   return string.format("Quaternion(scalar: %7.7f, vector: (%7.7f, %7.7f, %7.7f))",
        self[W], self[X], self[Y], self[Z]);
end
Quaternion.__tostring = Quaternion.ToString

function Quaternion.AngleBetween( a, b )
   a:Normalize();
   b:Normalize();
   local dot = Quaternion.DotProduct(a,b);
   return 2 * acos( dot / ( a:Magnitude() * b:Magnitude() ) )
end



------------------------------------------------
------------------------------------------------
-------------      MATRICES    -----------------
------------------------------------------------
------------------------------------------------
local X = 1;
local Y = 2;
local Z = 3;
local W = 4;

Matrix = {};
Matrix.__index = Matrix;
setmetatable(Matrix, {
   __call = function(self)
      local new = {
         1,0,0,0,
         0,1,0,0,
         0,0,1,0,
         0,0,0,1,
      }
      setmetatable(new, Matrix);
      return new;
   end
   })


local dot = Quaternion.DotProduct;

local r1,r2,r3,r4 = Quaternion(), Quaternion(), Quaternion(), Quaternion();
local c1,c2,c3,c4 = Quaternion(), Quaternion(), Quaternion(), Quaternion();
Matrix.__mul = function( m1, m2)
   local s;
   local m;
   if type(m1) == "number" then
      s = m1;
      m = m2;
   elseif type(m2) == "number" then
      s = m2;
      m = m1;
   end

   if s then
      local new = {
         s*m[1], s*m[2], s*m[3], s*m[4],
         s*m[5], s*m[6], s*m[7], s*m[8],
         s*m[9], s*m[10], s*m[11], s*m[12],
         s*m[13], s*m[14], s*m[15], s*m[16],
      }
      return setmetatable(new, Matrix);
   end

   -- using quaternions for a Vector4
   --[[
   local r1 = Quaternion( m1[1],m1[2],m1[3],m1[4]  )
   local r2 = Quaternion( m1[5],m1[6],m1[7],m1[8]  )
   local r3 = Quaternion( m1[9],m1[10],m1[11],m1[12]  )
   local r4 = Quaternion( m1[13],m1[14],m1[15],m1[16]  )

   local c1 = Quaternion( m2[1],m2[5],m2[9],m2[13]  )
   local c2 = Quaternion( m2[2],m2[6],m2[10],m2[14]  )
   local c3 = Quaternion( m2[3],m2[7],m2[11],m2[15]  )
   local c4 = Quaternion( m2[4],m2[8],m2[12],m2[16]  )
   --]]
   r1[X], r1[Y], r1[Z], r1[W] = m1[ 1], m1[ 2], m1[ 3], m1[ 4];
   r2[X], r2[Y], r2[Z], r2[W] = m1[ 5], m1[ 6], m1[ 7], m1[ 8];
   r3[X], r3[Y], r3[Z], r3[W] = m1[ 9], m1[10], m1[11], m1[12];
   r4[X], r4[Y], r4[Z], r4[W] = m1[13], m1[14], m1[15], m1[16];

   c1[X], c1[Y], c1[Z], c1[W] = m2[1], m2[5], m2[ 9], m2[13];
   c2[X], c2[Y], c2[Z], c2[W] = m2[2], m2[6], m2[10], m2[14];
   c3[X], c3[Y], c3[Z], c3[W] = m2[3], m2[7], m2[11], m2[15];
   c4[X], c4[Y], c4[Z], c4[W] = m2[4], m2[8], m2[12], m2[16];


   local self = {
      dot(r1,c1), dot(r1,c2), dot(r1,c3), dot(r1,c4),
      dot(r2,c1), dot(r2,c2), dot(r2,c3), dot(r2,c4),
      dot(r3,c1), dot(r3,c2), dot(r3,c3), dot(r3,c4),
      dot(r4,c1), dot(r4,c2), dot(r4,c3), dot(r4,c4),
   }
   return setmetatable(self, Matrix);

end


function Matrix:Identity()
   if not self then
      return Matrix()
   else
      self[1]  =  1;
      self[2]  =  0;
      self[3]  =  0;
      self[4]  =  0;
      self[5]  =  0;
      self[6]  =  1;
      self[7]  =  0;
      self[8]  =  0;
      self[9]  =  0;
      self[10] =  0;
      self[11] =  1;
      self[12] =  0;
      self[13] =  0;
      self[14] =  0;
      self[15] =  0;
      self[16] =  1;

   end
   return self;
end

local s = Matrix();
function Matrix:Scale( vector )

   local msg = "Matrix.Scale requires a Vector";
   if not self and not vector then
      error(msg);
   end
   if not vector then
      vector = self;
      self = nil;
   end
   if type(vector) ~= "table" or getmetatable(vector) ~= Vector then
      error(msg);
   end
   if not self then
      return Matrix():Scale( vector );
   else
      s:Identity();
      s[1]  =  vector[X];
      s[6]  =  vector[Y];
      s[11] =  vector[Z];
   end

   s = s * self;

   self[1] = s[1];
   self[2] = s[2];
   self[3] = s[3];
   self[4] = s[4];
   self[5] = s[5];
   self[6] = s[6];
   self[7] = s[7];
   self[8] = s[8];
   self[9] = s[9];
   self[10] = s[10];
   self[11] = s[11];
   self[12] = s[12];
   self[13] = s[13];
   self[14] = s[14];
   self[15] = s[15];
   self[16] = s[16];
   return self;
end

local t = Matrix();
function Matrix:Translate( vector )
   local msg = "Matrix.Translate requires a Vector";
   if not self and not vector then
      error(msg);
   end
   if not vector then
      vector = self;
      self = nil;
   end
   if type(vector) ~= "table" or getmetatable(vector) ~= Vector then
      error(msg);
   end
   if not self then
      return Matrix():Translate(vector);
   else
      t:Identity();
      t[13] = vector[X];
      t[14] = vector[Y];
      t[15] = vector[Z];
   end
   t = t * self;
   self[1] = t[1];
   self[2] = t[2];
   self[3] = t[3];
   self[4] = t[4];
   self[5] = t[5];
   self[6] = t[6];
   self[7] = t[7];
   self[8] = t[8];
   self[9] = t[9];
   self[10] = t[10];
   self[11] = t[11];
   self[12] = t[12];
   self[13] = t[13];
   self[14] = t[14];
   self[15] = t[15];
   self[16] = t[16];

   return self;
end

local r = Matrix();
function Matrix:Rotate( quat )
   local msg = "Matrix.Rotate requires a Quaternion";
   if not self and not quat then
      error(msg);
   end
   if not quat then
      quat = self;
      self = nil;
   end
   if type(quat) ~= "table" or getmetatable(quat) ~= Quaternion then
      error(msg);
   end
   if not self then
      return Matrix():Rotate( quat )
   else
      local x = quat[X];
      local y = quat[Y];
      local z = quat[Z];
      local w = quat[W] or 0;

      local x2 = x * x;
      local y2 = y * y;
      local z2 = z * z;
      local xy = x * y;
      local xz = x * z;
      local yz = y * z;
      local wx = w * x;
      local wy = w * y;
      local wz = w * z;


      r:Identity();
      r[1]  =  1 - 2 * (y2 + z2);
      r[2]  =  2 * (xy + wz);
      r[3]  =  2 * (xz - wy);
      r[5]  =  2 * (xy - wz);
      r[6]  =  1 - 2 * (x2 + z2);
      r[7]  =  2 * (yz + wx);
      r[9]  =  2 * (xz + wy);
      r[10] =  2 * (yz - wx);
      r[11] =  1 - 2 * (x2 + y2);
   end

   r = r * self;
    -- because i'm multplying in this order I can't just
    -- self:__mul(r);
   self[1] = r[1];
   self[2] = r[2];
   self[3] = r[3];
   self[4] = r[4];
   self[5] = r[5];
   self[6] = r[6];
   self[7] = r[7];
   self[8] = r[8];
   self[9] = r[9];
   self[10] = r[10];
   self[11] = r[11];
   self[12] = r[12];
   self[13] = r[13];
   self[14] = r[14];
   self[15] = r[15];
   self[16] = r[16];
   return self;
end





function Matrix:Transpose()
   local t = { unpack(self) }

   self[1] = t[1];
   self[2] = t[5];
   self[3] = t[9];
   self[4] = t[13];
   self[5] = t[2];
   self[6] = t[6];
   self[7] = t[10];
   self[8] = t[14];
   self[9] = t[3];
   self[10] = t[7];
   self[11] = t[11];
   self[12] = t[15];
   self[13] = t[4];
   self[14] = t[8];
   self[15] = t[12];
   self[16] = t[16];

   return self
end

function Matrix:__tostring()
   local r1 = string.format("%+7.7f , %+7.7f , %+7.7f , %+7.7f , \n",
      self[1], self[2], self[3], self[4] );
   local r2 = string.format("%+7.7f , %+7.7f , %+7.7f , %+7.7f , \n",
      self[5], self[6], self[7], self[8] );
   local r3 = string.format("%+7.7f , %+7.7f , %+7.7f , %+7.7f , \n",
      self[9], self[10], self[11], self[12] );
   local r4 = string.format("%+7.7f , %+7.7f , %+7.7f , %+7.7f , \n",
      self[13], self[14], self[15], self[16] );
   return r1 .. r2 .. r3 .. r4
end

local X = 1;
local Y = 2;
local Z = 3;
local W = 4;

-- x = pitch, y = yaw, z = roll;
-- applied in YXZ order
-- if you are keeping track at home: Z * X * Y
function Matrix:FromEuler( x, y, z)

   if not z then
      z = y;
      y = x;
      x = self;
      self = setmetatable({}, Matrix);
   end

   if type(z) ~= "number" then
      error("Matrix.FromEuler requires x,y,z numbers")
   end

   local sx = sin(x);
   local cx = cos(x);
   local sy = sin(y);
   local sy = cos(y);
   local sz = sin(z);
   local cz = cos(z);


   self[1]  =  sy * cx;
   self[2]  =  sx;
   self[3]  =  -sy * cx;
   self[4]  =  0;
   self[5]  =  -sy*sx*cz + sy*sz;
   self[6]  =  cx*cz;
   self[7]  =  sy*sx*cz + sy*sz;
   self[8]  =  0;
   self[9]  =  sy*sx*sz + sy*cz;
   self[10] =  -cx*sz;
   self[11] =  -sy*sx*sz + sy*cz;
   self[12] =  0;
   self[13] =  0;
   self[14] =  0;
   self[15] =  0;
   self[16] =  1;

   return self;
end



function Matrix:FromQuaternion( quat )
   if not quat then
      quat = self;
      self = Matrix();
   end

   if type(quat) ~= table and #quat < 3 then
      error("You must pass a Quaternion to Matrix.FromQuaternion")
   end
   local x = quat[X];
   local y = quat[Y];
   local z = quat[Z];
   local w = quat[W] or 0;



   local x2 = x * x;
   local y2 = y * y;
   local z2 = z * z;
   local xy = x * y;
   local xz = x * z;
   local yz = y * z;
   local wx = w * x;
   local wy = w * y;
   local wz = w * z;


   self[1]  =  1 - 2 * (y2 + z2);
   self[2]  =  2 * (xy + wz);
   self[3]  =  2 * (xz - wy);
   self[4]  =  0;
   self[5]  =  2 * (xy - wz);
   self[6]  =  1 - 2 * (x2 + z2);
   self[7]  =  2 * (yz + wx);
   self[8]  =  0;
   self[9]  =  2 * (xz + wy);
   self[10] =  2 * (yz - wx);
   self[11] =  1 - 2 * (x2 + y2);
   self[12] =  0;
   self[13] =  0;
   self[14] =  0;
   self[15] =  0;
   self[16] =  1;


   --[[
   {
      1 - 2 * (y2 + z2),     2 * (xy + wz),     2 * (xz - wy), 0,
          2 * (xy - wz), 1 - 2 * (x2 + z2),     2 * (yz + wx), 0,
          2 * (xz + wy),     2 * (yz - wx), 1 - 2 * (x2 + y2), 0,
                      0,                 0,                 0, 1,
   }
   --]]
   return self;
end


-- equivalent to
-- rotationMatrix * translationMatrix;
function Matrix:FromQuaternionAtVector( quat, vector)
  if not vector then
    vector = quat;
    quat = self;
    self = Matrix();
  end
  if type(quat) ~= "table" or #quat < 4 then
    error("Matrix.FromQuaternionAtVector requires a quaternion and a vector");
  elseif type(vector) ~= "table" or #vector < 3 then
    error("Matrix.FromQuaternionAtVector requires a quaternion and a vector")
  end

  self:FromQuaternion( quat )
  self[13] = vector[X];
  self[14] = vector[Y];
  self[15] = vector[Z];

  return self;
end


-- equivalent to
-- translationMatrix * rotationMatrix
-- the 4th value in this matrix multplication always end up as 0
do -- to keep these locals local
   local r4 = Vector();
   local c1,c2,c3,c4 = Vector(), Vector(), Vector();
   local dot = Vector.DotProduct;
   function Matrix:FromVectorAroundQuaternion( vector, quat)
     if not quat then
       quat = vector;
       vector = self;
       self = Matrix();
     end
     if type(quat) ~= "table" or #quat < 4 then
       error("Matrix.FromVectorAroundQuaternion requires vector, quaternion");
     elseif type(vector) ~= "table" or #vector < 3 then
       error("Matrix.FromVectorAroundQuaternion requires vector, quaternion")
     end

     -- set our 3x3 rotation matrix
     self:FromQuaternion( quat )

     -- set our critical rows and columns
     r4[X], r4[Y], r4[Z], r4[W] = vector[X], vector[Y], vector[Z];

     c1[X], c1[Y], c1[Z], c1[W] = self[1], self[5], self[ 9];
     c2[X], c2[Y], c2[Z], c2[W] = self[2], self[6], self[10];
     c3[X], c3[Y], c3[Z], c3[W] = self[3], self[7], self[11];


     r4 = {vector[X], vector[Y], vector[Z], 1}

     self[13] = dot(r4,c1);
     self[14] = dot(r4,c2);
     self[15] = dot(r4,c3);

     return self;
   end
end

-- translation * rotation * translation
-- TranslationMatrix(vec2) * rotationMatrix(quat) * translationMatrix(vec1)
function Matrix:FromVectorAroundQuaternionAtVector( vec1, quat, vec2 )
  if not vec2 then
    vec2 = quat;
    quat = vec1;
    vec1 = self;
    self = Matrix();
  end
  if type(quat) ~= "table" or #quat < 4 then
    error("Matrix.FromVectorAroundQuaternionAtVector requires vector, quat, vector");
  elseif type(vec2) ~= "table" or #vec2 < 3 then
     error("Matrix.FromVectorAroundQuaternionAtVector requires vector, quat, vector");
  elseif type(vec1) ~= "table" or #vec1 < 3 then
      error("Matrix.FromVectorAroundQuaternionAtVector requires vector, quat, vector");
  end
  -- rotation * translation;
  self:FromQuaternionAtVector( quat,vec2 );

    -- set our critical rows and columns
  r4[X], r4[Y], r4[Z], r4[W] = vec1[X], vec1[Y], vec1[Z], 1;

  c1[X], c1[Y], c1[Z], c1[W] = self[1], self[5], self[ 9], self[13];
  c2[X], c2[Y], c2[Z], c2[W] = self[2], self[6], self[10], self[14];
  c3[X], c3[Y], c3[Z], c3[W] = self[3], self[7], self[11], self[15];

  self[13] = dot(r4,c1);
  self[14] = dot(r4,c2);
  self[15] = dot(r4,c3);

  return self;
end

function Matrix:Inverse()

  local inv = Matrix();

  -- code was lifted from MESA 3D
  inv[1] = self[6]  * self[11] * self[16] -
        self[6]  * self[12] * self[15] -
        self[10]  * self[7]  * self[16] +
        self[10]  * self[8]  * self[15] +
        self[14] * self[7]  * self[12] -
        self[14] * self[8]  * self[11];

  inv[5] = -self[5]  * self[11] * self[16] +
           self[5]  * self[12] * self[15] +
           self[9]  * self[7]  * self[16] -
           self[9]  * self[8]  * self[15] -
           self[13] * self[7]  * self[12] +
           self[13] * self[8]  * self[11];

  inv[9] = self[5]  * self[10] * self[16] -
          self[5]  * self[12] * self[14] -
          self[9]  * self[6] * self[16] +
          self[9]  * self[8] * self[14] +
          self[13] * self[6] * self[12] -
          self[13] * self[8] * self[10];

  inv[13] = -self[5]  * self[10] * self[15] +
            self[5]  * self[11] * self[14] +
            self[9]  * self[6] * self[15] -
            self[9]  * self[7] * self[14] -
            self[13] * self[6] * self[11] +
            self[13] * self[7] * self[10];

  inv[2] = -self[2]  * self[11] * self[16] +
           self[2]  * self[12] * self[15] +
           self[10]  * self[3] * self[16] -
           self[10]  * self[4] * self[15] -
           self[14] * self[3] * self[12] +
           self[14] * self[4] * self[11];

  inv[6] = self[1]  * self[11] * self[16] -
          self[1]  * self[12] * self[15] -
          self[9]  * self[3] * self[16] +
          self[9]  * self[4] * self[15] +
          self[13] * self[3] * self[12] -
          self[13] * self[4] * self[11];

  inv[10] = -self[1]  * self[10] * self[16] +
           self[1]  * self[12] * self[14] +
           self[9]  * self[2] * self[16] -
           self[9]  * self[4] * self[14] -
           self[13] * self[2] * self[12] +
           self[13] * self[4] * self[10];

  inv[14] = self[1]  * self[10] * self[15] -
           self[1]  * self[11] * self[14] -
           self[9]  * self[2] * self[15] +
           self[9]  * self[3] * self[14] +
           self[13] * self[2] * self[11] -
           self[13] * self[3] * self[10];

  inv[3] = self[2]  * self[7] * self[16] -
          self[2]  * self[8] * self[15] -
          self[6]  * self[3] * self[16] +
          self[6]  * self[4] * self[15] +
          self[14] * self[3] * self[8] -
          self[14] * self[4] * self[7];

  inv[7] = -self[1]  * self[7] * self[16] +
           self[1]  * self[8] * self[15] +
           self[5]  * self[3] * self[16] -
           self[5]  * self[4] * self[15] -
           self[13] * self[3] * self[8] +
           self[13] * self[4] * self[7];

  inv[11] = self[1]  * self[6] * self[16] -
           self[1]  * self[8] * self[14] -
           self[5]  * self[2] * self[16] +
           self[5]  * self[4] * self[14] +
           self[13] * self[2] * self[8] -
           self[13] * self[4] * self[6];

  inv[15] = -self[1]  * self[6] * self[15] +
            self[1]  * self[7] * self[14] +
            self[5]  * self[2] * self[15] -
            self[5]  * self[3] * self[14] -
            self[13] * self[2] * self[7] +
            self[13] * self[3] * self[6];

  inv[4] = -self[2] * self[7] * self[12] +
           self[2] * self[8] * self[11] +
           self[6] * self[3] * self[12] -
           self[6] * self[4] * self[11] -
           self[10] * self[3] * self[8] +
           self[10] * self[4] * self[7];

  inv[8] = self[1] * self[7] * self[12] -
          self[1] * self[8] * self[11] -
          self[5] * self[3] * self[12] +
          self[5] * self[4] * self[11] +
          self[9] * self[3] * self[8] -
          self[9] * self[4] * self[7];

  inv[12] = -self[1] * self[6] * self[12] +
            self[1] * self[8] * self[10] +
            self[5] * self[2] * self[12] -
            self[5] * self[4] * self[10] -
            self[9] * self[2] * self[8] +
            self[9] * self[4] * self[6];

  inv[16] = self[1] * self[6] * self[11] -
           self[1] * self[7] * self[10] -
           self[5] * self[2] * self[11] +
           self[5] * self[3] * self[10] +
           self[9] * self[2] * self[7] -
           self[9] * self[3] * self[6];

    local det = self[1] * inv[1] + self[2] * inv[5] + self[3] * inv[9] + self[4] * inv[13];

    if det == 0 then
      error("Determinate in Matrix.Inverse cannot be 0")
    end
    det = 1.0 / det;

   for i = 1,16 do
      inv[i] = inv[i] * det;
   end

   return inv;
end

-- end definition
MATHS = true;
