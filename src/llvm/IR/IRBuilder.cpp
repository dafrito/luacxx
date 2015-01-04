#include "IRBuilder.hpp"

#include <llvm/Analysis/Passes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/IR/IRBuilder.h>

#include "Value.hpp"
#include "BranchInst.hpp"
#include "Instruction.hpp"
#include "../../std/vector.hpp"

#include "../../algorithm.hpp"
#include "../../thread.hpp"
#include "../../convert/callable.hpp"
#include "../../convert/const_char_p.hpp"
#include "../../convert/numeric.hpp"

using namespace llvm;

int IRBuilder_Insert(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);

    if (lua_gettop(state) > 2) {
        lua::push(state, self->Insert(
            lua::get<Instruction*>(state, 2),
            lua::get<const char*>(state, 3)
        ));
        return 1;
    }

    lua::push(state, self->Insert(
        lua::get<Instruction*>(state, 2)
    ));
    return 1;
}

int IRBuilder_CreateAggregateRet(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);

    if (lua_gettop(state) == 2 && lua_type(state, 2) == LUA_TTABLE) {
        std::vector<Value*> retVals;
        lua::store(retVals, state, 2);
        lua::push(state, self->CreateAggregateRet(
            &retVals[0],
            retVals.size()
        ));
        return 1;
    }

    lua::push(state, self->CreateAggregateRet(
        lua::get<Value* const*>(state, 2),
        lua::get<unsigned>(state, 3)
    ));
    return 1;
}

int IRBuilder_CreateCondBr(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);

    if (lua_gettop(state) > 4) {
        lua::push(state, self->CreateCondBr(
            lua::get<Value*>(state, 2),
            lua::get<BasicBlock*>(state, 3),
            lua::get<BasicBlock*>(state, 4),
            lua::get<MDNode*>(state, 5)
        ));
        return 1;
    }

    lua::push(state, self->CreateCondBr(
        lua::get<Value*>(state, 2),
        lua::get<BasicBlock*>(state, 3),
        lua::get<BasicBlock*>(state, 4)
    ));
    return 1;
}

int IRBuilder_CreateSwitch(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);

    // CreateSwitch (Value *V, BasicBlock *Dest, unsigned NumCases=10, MDNode *BranchWeights=nullptr)
    switch (lua_gettop(state)) {
    case 3:
    {
        lua::push(state, self->CreateSwitch(
            lua::get<Value*>(state, 2),
            lua::get<BasicBlock*>(state, 3)
        ));
        break;
    }
    case 4:
    {
        lua::push(state, self->CreateSwitch(
            lua::get<Value*>(state, 2),
            lua::get<BasicBlock*>(state, 3),
            lua::get<unsigned>(state, 4)
        ));
        break;
    }
    case 5:
    default:
        lua::push(state, self->CreateSwitch(
            lua::get<Value*>(state, 2),
            lua::get<BasicBlock*>(state, 3),
            lua::get<unsigned>(state, 4),
            lua::get<MDNode*>(state, 5)
        ));
        break;
    }
    return 1;
}

int IRBuilder_CreateIndirectBr(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);
    if (lua_gettop(state) > 2) {
        lua::push(state, self->CreateIndirectBr(
            lua::get<Value*>(state, 2),
            lua::get<unsigned>(state, 3)
        ));
        return 1;
    }
    lua::push(state, self->CreateIndirectBr(
        lua::get<Value*>(state, 2)
    ));
    return 1;
}

int IRBuilder_CreateInvoke(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateResume(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateUnreachable(lua_State* const state)
{
    return 1;
}

// Value* CreateAdd (Value *LHS, Value *RHS, const Twine &Name="", bool HasNUW=false, bool HasNSW=false)
int IRBuilder_CreateAdd(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);

    switch (lua_gettop(state)) {
    case 3:
    {
        lua::push(state, self->CreateAdd(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3)
        ));
        break;
    }
    case 4:
    {
        lua::push(state, self->CreateAdd(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3),
            lua::get<const char*>(state, 4)
        ));
        break;
    }
    case 5:
    {
        lua::push(state, self->CreateAdd(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3),
            lua::get<const char*>(state, 4),
            lua::get<bool>(state, 5)
        ));
        break;
    }
    case 6:
    default:
        lua::push(state, self->CreateAdd(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3),
            lua::get<const char*>(state, 4),
            lua::get<bool>(state, 5),
            lua::get<bool>(state, 6)
        ));
        break;
    }
    return 1;
}

// Value *  CreateNSWAdd (Value *LHS, Value *RHS, const Twine &Name="")
int IRBuilder_CreateNSWAdd(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);
    if (lua_gettop(state) == 3) {
        lua::push(state, self->CreateNSWAdd(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3)
        ));
        return 1;
    }
    lua::push(state, self->CreateNSWAdd(
        lua::get<Value*>(state, 2),
        lua::get<Value*>(state, 3),
        lua::get<const char*>(state, 4)
    ));
    return 1;
}

// Value *  CreateNUWAdd (Value *LHS, Value *RHS, const Twine &Name="")
int IRBuilder_CreateNUWAdd(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);
    if (lua_gettop(state) == 3) {
        lua::push(state, self->CreateNUWAdd(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3)
        ));
        return 1;
    }
    lua::push(state, self->CreateNUWAdd(
        lua::get<Value*>(state, 2),
        lua::get<Value*>(state, 3),
        lua::get<const char*>(state, 4)
    ));
    return 1;
}

int IRBuilder_CreateFAdd(lua_State* const state)
{
    return 1;
}

// Value* CreateSub (Value *LHS, Value *RHS, const Twine &Name="", bool HasNUW=false, bool HasNSW=false)
int IRBuilder_CreateSub(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);

    switch (lua_gettop(state)) {
    case 3:
    {
        lua::push(state, self->CreateSub(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3)
        ));
        break;
    }
    case 4:
    {
        lua::push(state, self->CreateSub(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3),
            lua::get<const char*>(state, 4)
        ));
        break;
    }
    case 5:
    {
        lua::push(state, self->CreateSub(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3),
            lua::get<const char*>(state, 4),
            lua::get<bool>(state, 5)
        ));
        break;
    }
    case 6:
    default:
        lua::push(state, self->CreateSub(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3),
            lua::get<const char*>(state, 4),
            lua::get<bool>(state, 5),
            lua::get<bool>(state, 6)
        ));
        break;
    }
    return 1;
}

// Value *  CreateNSWSub (Value *LHS, Value *RHS, const Twine &Name="")
int IRBuilder_CreateNSWSub(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);
    if (lua_gettop(state) == 3) {
        lua::push(state, self->CreateNSWSub(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3)
        ));
        return 1;
    }
    lua::push(state, self->CreateNSWSub(
        lua::get<Value*>(state, 2),
        lua::get<Value*>(state, 3),
        lua::get<const char*>(state, 4)
    ));
    return 1;
}

// Value *  CreateNUWSub (Value *LHS, Value *RHS, const Twine &Name="")
int IRBuilder_CreateNUWSub(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);
    if (lua_gettop(state) == 3) {
        lua::push(state, self->CreateNUWSub(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3)
        ));
        return 1;
    }
    lua::push(state, self->CreateNUWSub(
        lua::get<Value*>(state, 2),
        lua::get<Value*>(state, 3),
        lua::get<const char*>(state, 4)
    ));
    return 1;
}

int IRBuilder_CreateFSub(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateMul(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateNSWMul(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateNUWMul(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFMul(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateUDiv(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateExactUDiv(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateSDiv(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateExactSDiv(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFDiv(lua_State* const state)
{
    return 1;
}

// Value *  CreateURem (Value *LHS, Value *RHS, const Twine &Name="")
int IRBuilder_CreateURem(lua_State* const state)
{
    auto self = lua::get<IRBuilder<>*>(state, 1);
    if (lua_gettop(state) == 3) {
        lua::push(state, self->CreateURem(
            lua::get<Value*>(state, 2),
            lua::get<Value*>(state, 3)
        ));
        return 1;
    }
    lua::push(state, self->CreateURem(
        lua::get<Value*>(state, 2),
        lua::get<Value*>(state, 3),
        lua::get<const char*>(state, 4)
    ));
    return 1;
}

int IRBuilder_CreateFRem(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateShl(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateLShr(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateAShr(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateAnd(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateOr(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateXor(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateBinOp(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateNeg(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateNSWNeg(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateNUWNeg(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFNeg(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateNot(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateAlloca(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateLoad(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateStore(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateAlignedLoad(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateAlignedStore(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFence(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateAtomicCmpXchg(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateAtomicRMW(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateGEP(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateInBoundsGEP(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateConstGEP1_32(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateConstInBoundsGEP1_32(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateConstGEP2_32(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateConstInBoundsGEP2_32(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateConstGEP1_64(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateConstInBoundsGEP1_64(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateConstGEP2_64(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateConstInBoundsGEP2_64(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateStructGEP(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateGlobalStringPtr(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateTrunc(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateZExt(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateSExt(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateZExtOrTrunc(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateSExtOrTrunc(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFPToUI(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFPToSI(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateUIToFP(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateSIToFP(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFPTrunc(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFPExt(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreatePtrToInt(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateIntToPtr(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateBitCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateAddrSpaceCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateZExtOrBitCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateSExtOrBitCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateTruncOrBitCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreatePointerCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateIntCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFPCast(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpEQ(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpNE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpUGT(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpUGE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpULT(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpULE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpSGT(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpSGE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpSLT(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmpSLE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpOEQ(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpOGT(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpOGE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpOLT(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpOLE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpONE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpORD(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpUNO(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpUEQ(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpUGT(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpUGE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpULT(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpULE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmpUNE(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateICmp(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateFCmp(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreatePHI(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateCall(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateSelect(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateVAArg(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateExtractElement(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateInsertElement(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateShuffleVector(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateExtractValue(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateInsertValue(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateLandingPad(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateIsNull(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateIsNotNull(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreatePtrDiff(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateVectorSplat(lua_State* const state)
{
    return 1;
}

int IRBuilder_CreateExtractInteger(lua_State* const state)
{
    return 1;
}

void lua::llvm_IRBuilder_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["getFolder"] = &IRBuilder<>::getFolder;
    mt["isNamePreserving"] = &IRBuilder<>::isNamePreserving;
    mt["Insert"] = IRBuilder_Insert;
    mt["CreateRetVoid"] = &IRBuilder<>::CreateRetVoid;
    mt["CreateRet"] = &IRBuilder<>::CreateRet;
    mt["CreateAggregateRet"] = IRBuilder_CreateAggregateRet;
    mt["CreateBr"] = &IRBuilder<>::CreateBr;
    mt["CreateCondBr"] = IRBuilder_CreateCondBr;
    mt["CreateSwitch"] = IRBuilder_CreateSwitch;
    mt["CreateIndirectBr"] = IRBuilder_CreateIndirectBr;
    mt["CreateInvoke"] = IRBuilder_CreateInvoke;
    mt["CreateResume"] = &IRBuilder<>::CreateResume;
    mt["CreateUnreachable"] = &IRBuilder<>::CreateUnreachable;
    mt["CreateAdd"] = IRBuilder_CreateAdd;
    mt["CreateNSWAdd"] = IRBuilder_CreateNSWAdd;
    mt["CreateNUWAdd"] = IRBuilder_CreateNUWAdd;
    mt["CreateFAdd"] = IRBuilder_CreateFAdd;
    mt["CreateSub"] = IRBuilder_CreateSub;
    mt["CreateNSWSub"] = IRBuilder_CreateNSWSub;
    mt["CreateNUWSub"] = IRBuilder_CreateNUWSub;
    mt["CreateFSub"] = IRBuilder_CreateFSub;
    mt["CreateMul"] = IRBuilder_CreateMul;
    mt["CreateNSWMul"] = IRBuilder_CreateNSWMul;
    mt["CreateNUWMul"] = IRBuilder_CreateNUWMul;
    mt["CreateFMul"] = IRBuilder_CreateFMul;
    mt["CreateUDiv"] = IRBuilder_CreateUDiv;
    mt["CreateExactUDiv"] = IRBuilder_CreateExactUDiv;
    mt["CreateSDiv"] = IRBuilder_CreateSDiv;
    mt["CreateExactSDiv"] = IRBuilder_CreateExactSDiv;
    mt["CreateFDiv"] = IRBuilder_CreateFDiv;
    mt["CreateURem"] = IRBuilder_CreateURem;
    mt["CreateFRem"] = IRBuilder_CreateFRem;
    mt["CreateShl"] = IRBuilder_CreateShl;
    mt["CreateLShr"] = IRBuilder_CreateLShr;
    mt["CreateAShr"] = IRBuilder_CreateAShr;
    mt["CreateAnd"] = IRBuilder_CreateAnd;
    mt["CreateOr"] = IRBuilder_CreateOr;
    mt["CreateXor"] = IRBuilder_CreateXor;
    mt["CreateBinOp"] = IRBuilder_CreateBinOp;
    mt["CreateNeg"] = IRBuilder_CreateNeg;
    mt["CreateNSWNeg"] = IRBuilder_CreateNSWNeg;
    mt["CreateNUWNeg"] = IRBuilder_CreateNUWNeg;
    mt["CreateFNeg"] = IRBuilder_CreateFNeg;
    mt["CreateNot"] = IRBuilder_CreateNot;
    mt["CreateAlloca"] = IRBuilder_CreateAlloca;
    mt["CreateLoad"] = IRBuilder_CreateLoad;
    mt["CreateStore"] = IRBuilder_CreateStore;
    mt["CreateAlignedLoad"] = IRBuilder_CreateAlignedLoad;
    mt["CreateAlignedStore"] = IRBuilder_CreateAlignedStore;
    mt["CreateFence"] = IRBuilder_CreateFence;
    mt["CreateAtomicCmpXchg"] = IRBuilder_CreateAtomicCmpXchg;
    mt["CreateAtomicRMW"] = IRBuilder_CreateAtomicRMW;
    mt["CreateGEP"] = IRBuilder_CreateGEP;
    mt["CreateInBoundsGEP"] = IRBuilder_CreateInBoundsGEP;
    mt["CreateConstGEP1_32"] = IRBuilder_CreateConstGEP1_32;
    mt["CreateConstInBoundsGEP1_32"] = IRBuilder_CreateConstInBoundsGEP1_32;
    mt["CreateConstGEP2_32"] = IRBuilder_CreateConstGEP2_32;
    mt["CreateConstInBoundsGEP2_32"] = IRBuilder_CreateConstInBoundsGEP2_32;
    mt["CreateConstGEP1_64"] = IRBuilder_CreateConstGEP1_64;
    mt["CreateConstInBoundsGEP1_64"] = IRBuilder_CreateConstInBoundsGEP1_64;
    mt["CreateConstGEP2_64"] = IRBuilder_CreateConstGEP2_64;
    mt["CreateConstInBoundsGEP2_64"] = IRBuilder_CreateConstInBoundsGEP2_64;
    mt["CreateStructGEP"] = IRBuilder_CreateStructGEP;
    mt["CreateGlobalStringPtr"] = IRBuilder_CreateGlobalStringPtr;
    mt["CreateTrunc"] = IRBuilder_CreateTrunc;
    mt["CreateZExt"] = IRBuilder_CreateZExt;
    mt["CreateSExt"] = IRBuilder_CreateSExt;
    mt["CreateZExtOrTrunc"] = IRBuilder_CreateZExtOrTrunc;
    mt["CreateSExtOrTrunc"] = IRBuilder_CreateSExtOrTrunc;
    mt["CreateFPToUI"] = IRBuilder_CreateFPToUI;
    mt["CreateFPToSI"] = IRBuilder_CreateFPToSI;
    mt["CreateUIToFP"] = IRBuilder_CreateUIToFP;
    mt["CreateSIToFP"] = IRBuilder_CreateSIToFP;
    mt["CreateFPTrunc"] = IRBuilder_CreateFPTrunc;
    mt["CreateFPExt"] = IRBuilder_CreateFPExt;
    mt["CreatePtrToInt"] = IRBuilder_CreatePtrToInt;
    mt["CreateIntToPtr"] = IRBuilder_CreateIntToPtr;
    mt["CreateBitCast"] = IRBuilder_CreateBitCast;
    mt["CreateAddrSpaceCast"] = IRBuilder_CreateAddrSpaceCast;
    mt["CreateZExtOrBitCast"] = IRBuilder_CreateZExtOrBitCast;
    mt["CreateSExtOrBitCast"] = IRBuilder_CreateSExtOrBitCast;
    mt["CreateTruncOrBitCast"] = IRBuilder_CreateTruncOrBitCast;
    mt["CreateCast"] = IRBuilder_CreateCast;
    mt["CreatePointerCast"] = IRBuilder_CreatePointerCast;
    mt["CreateIntCast"] = IRBuilder_CreateIntCast;
    mt["CreateFPCast"] = IRBuilder_CreateFPCast;
    mt["CreateICmpEQ"] = IRBuilder_CreateICmpEQ;
    mt["CreateICmpNE"] = IRBuilder_CreateICmpNE;
    mt["CreateICmpUGT"] = IRBuilder_CreateICmpUGT;
    mt["CreateICmpUGE"] = IRBuilder_CreateICmpUGE;
    mt["CreateICmpULT"] = IRBuilder_CreateICmpULT;
    mt["CreateICmpULE"] = IRBuilder_CreateICmpULE;
    mt["CreateICmpSGT"] = IRBuilder_CreateICmpSGT;
    mt["CreateICmpSGE"] = IRBuilder_CreateICmpSGE;
    mt["CreateICmpSLT"] = IRBuilder_CreateICmpSLT;
    mt["CreateICmpSLE"] = IRBuilder_CreateICmpSLE;
    mt["CreateFCmpOEQ"] = IRBuilder_CreateFCmpOEQ;
    mt["CreateFCmpOGT"] = IRBuilder_CreateFCmpOGT;
    mt["CreateFCmpOGE"] = IRBuilder_CreateFCmpOGE;
    mt["CreateFCmpOLT"] = IRBuilder_CreateFCmpOLT;
    mt["CreateFCmpOLE"] = IRBuilder_CreateFCmpOLE;
    mt["CreateFCmpONE"] = IRBuilder_CreateFCmpONE;
    mt["CreateFCmpORD"] = IRBuilder_CreateFCmpORD;
    mt["CreateFCmpUNO"] = IRBuilder_CreateFCmpUNO;
    mt["CreateFCmpUEQ"] = IRBuilder_CreateFCmpUEQ;
    mt["CreateFCmpUGT"] = IRBuilder_CreateFCmpUGT;
    mt["CreateFCmpUGE"] = IRBuilder_CreateFCmpUGE;
    mt["CreateFCmpULT"] = IRBuilder_CreateFCmpULT;
    mt["CreateFCmpULE"] = IRBuilder_CreateFCmpULE;
    mt["CreateFCmpUNE"] = IRBuilder_CreateFCmpUNE;
    mt["CreateICmp"] = IRBuilder_CreateICmp;
    mt["CreateFCmp"] = IRBuilder_CreateFCmp;
    mt["CreatePHI"] = IRBuilder_CreatePHI;
    mt["CreateCall"] = IRBuilder_CreateCall;
    mt["CreateSelect"] = IRBuilder_CreateSelect;
    mt["CreateVAArg"] = IRBuilder_CreateVAArg;
    mt["CreateExtractElement"] = IRBuilder_CreateExtractElement;
    mt["CreateInsertElement"] = IRBuilder_CreateInsertElement;
    mt["CreateShuffleVector"] = IRBuilder_CreateShuffleVector;
    mt["CreateExtractValue"] = IRBuilder_CreateExtractValue;
    mt["CreateInsertValue"] = IRBuilder_CreateInsertValue;
    mt["CreateLandingPad"] = IRBuilder_CreateLandingPad;
    mt["CreateIsNull"] = IRBuilder_CreateIsNull;
    mt["CreateIsNotNull"] = IRBuilder_CreateIsNotNull;
    mt["CreatePtrDiff"] = IRBuilder_CreatePtrDiff;
    mt["CreateVectorSplat"] = IRBuilder_CreateVectorSplat;
    mt["CreateExtractInteger"] = IRBuilder_CreateExtractInteger;
}

int IRBuilder_new(lua_State* const state)
{
    if (lua::is_type<Instruction>(state, 2)) {
        // IRBuilder (Instruction *IP, MDNode *FPMathTag=nullptr)
        if (lua_gettop(state) > 2) {
            lua::make<IRBuilder<>>(state,
                lua::get<Instruction*>(state, 2),
                lua::get<MDNode*>(state, 3)
            );
        } else {
            lua::make<IRBuilder<>>(state,
                lua::get<Instruction*>(state, 2)
            );
        }
        return 1;
    }

    if (lua::is_type<Use>(state, 2)) {
        // IRBuilder (Use &U, MDNode *FPMathTag=nullptr)
        if (lua_gettop(state) > 2) {
            lua::make<IRBuilder<>>(state,
                lua::get<Use&>(state, 2),
                lua::get<MDNode*>(state, 3)
            );
        } else {
            lua::make<IRBuilder<>>(state,
                lua::get<Use&>(state, 2)
            );
        }
        return 1;
    }

    if (lua::is_type<LLVMContext>(state, 2)) {
        // IRBuilder (LLVMContext &C, MDNode *FPMathTag=nullptr)
        if (lua_gettop(state) == 2) {
            lua::make<IRBuilder<>>(state,
                lua::get<LLVMContext&>(state, 2)
            );
            return 1;
        }

        if (lua::is_type<MDNode>(state, 3)) {
            lua::make<IRBuilder<>>(state,
                lua::get<LLVMContext&>(state, 2),
                lua::get<MDNode*>(state, 3)
            );
            return 1;
        }

        // IRBuilder (LLVMContext &C, const T &F, const Inserter &I=Inserter(), MDNode *FPMathTag=nullptr)
        switch (lua_gettop(state)) {
        case 3:
        {
            lua::make<IRBuilder<>>(state,
                lua::get<LLVMContext&>(state, 2),
                lua::get<ConstantFolder&>(state, 3)
            );
            return 1;
        }
        case 4:
        {
            lua::make<IRBuilder<>>(state,
                lua::get<LLVMContext&>(state, 2),
                lua::get<ConstantFolder&>(state, 3),
                lua::get<const IRBuilderDefaultInserter<true>&>(state, 4)
            );
            return 1;
        }
        }

        lua::make<IRBuilder<>>(state,
            lua::get<LLVMContext&>(state, 2),
            lua::get<ConstantFolder&>(state, 3),
            lua::get<const IRBuilderDefaultInserter<true>&>(state, 4),
            lua::get<MDNode*>(state, 5)
        );
        return 1;
    }

    if (lua::is_type<BasicBlock>(state, 2)) {
        if (lua_gettop(state) == 2) {
            // IRBuilder (BasicBlock *TheBB)
            lua::make<IRBuilder<>>(state,
                lua::get<BasicBlock*>(state, 2)
            );
            return 1;
        }

        if (lua::is_type<MDNode>(state, 3)) {
            // IRBuilder (BasicBlock *TheBB, MDNode *FPMathTag=nullptr)
            lua::make<IRBuilder<>>(state,
                lua::get<BasicBlock*>(state, 2),
                lua::get<MDNode*>(state, 3)
            );
            return 1;
        }

        if (lua::is_type<BasicBlock::iterator>(state, 3)) {
            if (lua_gettop(state) == 3) {
                // IRBuilder (BasicBlock *TheBB, BasicBlock::iterator IP)
                return 1;
            }
            if (lua::is_type<MDNode>(state, 4)) {
                // IRBuilder (BasicBlock *TheBB, BasicBlock::iterator IP, MDNode *FPMathTag=nullptr)
                lua::make<IRBuilder<>>(state,
                    lua::get<BasicBlock*>(state, 2),
                    lua::get<BasicBlock::iterator>(state, 3),
                    lua::get<MDNode*>(state, 4)
                );
                return 1;
            }

            if (lua_gettop(state) == 4) {
                lua::make<IRBuilder<>>(state,
                    lua::get<BasicBlock*>(state, 2),
                    lua::get<BasicBlock::iterator>(state, 3),
                    lua::get<const ConstantFolder&>(state, 4)
                );
                return 1;
            }

            // IRBuilder (BasicBlock *TheBB, BasicBlock::iterator IP, const T &F, MDNode *FPMathTag=nullptr)
            lua::make<IRBuilder<>>(state,
                lua::get<BasicBlock*>(state, 2),
                lua::get<BasicBlock::iterator>(state, 3),
                lua::get<const ConstantFolder&>(state, 4),
                lua::get<MDNode*>(state, 5)
            );
            return 1;
        }

        if (lua::is_type<ConstantFolder>(state, 3)) {
            // IRBuilder (BasicBlock *TheBB, const T &F, MDNode *FPMathTag=nullptr)
            if (lua_gettop(state) == 3) {
                lua::make<IRBuilder<>>(state,
                    lua::get<BasicBlock*>(state, 2),
                    lua::get<const ConstantFolder&>(state, 3)
                );
                return 1;
            }
            lua::make<IRBuilder<>>(state,
                lua::get<BasicBlock*>(state, 2),
                lua::get<const ConstantFolder&>(state, 3),
                lua::get<MDNode*>(state, 4)
            );
            return 1;
        }

    }

    return 1;
}

int luaopen_llvm_IRBuilder(lua_State* const state)
{
    lua::thread env(state);

    if (!env["llvm"]) {
        env["llvm"] = lua::value::table;
    }

    env["llvm"]["IRBuilder"] = lua::value::table;
    env["llvm"]["IRBuilder"]["new"] = IRBuilder_new;

    return 0;
}
