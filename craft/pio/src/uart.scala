package sifive.blocks.pio

import chisel3._
// import chisel3.{withClockAndReset, _}
import chisel3.util._
import chisel3.experimental._

import freechips.rocketchip.config._
import freechips.rocketchip.diplomacy._
import freechips.rocketchip.amba.axi4._
import freechips.rocketchip.amba.apb._
import freechips.rocketchip.amba.ahb._
import freechips.rocketchip.interrupts._
import freechips.rocketchip.util.{ElaborationArtefacts}
import freechips.rocketchip.tilelink._
import freechips.rocketchip.subsystem._
import freechips.rocketchip.regmapper._
import freechips.rocketchip.devices.debug.Debug
import freechips.rocketchip.diplomaticobjectmodel.ConstructOM

import sifive.skeleton._

import sifive.blocks.devices.uart._

class WithDummyUARTConfig extends Config(Parameters.empty)

class SkeletonUartDUT(harness: LazyScope)(implicit p: Parameters) extends SkeletonDUT(harness)
{
	val uartAttachParams = UARTAttachParams(
	    UARTParams(address = 0x10013000,
	      dataBits = 9,
	      includeFourWire = true,
	      includeParity = true,
	      includeIndependentParity = false),
	    19,
	    cbus,
	    ibus.fromSync)
	val uart = UART.attach(uartAttachParams)
	val uartNode = BundleBridgeSink[UARTPortIO]()
	uartNode := uart.ioNode

	InModuleBody {	UART.loopback(uartNode.bundle)	}
}

class SkeletonUartTestHarness()(implicit p: Parameters) extends LazyModule with LazyScope
{
  val dut = LazyModule(new SkeletonUartDUT(this))
  lazy val module = new LazyModuleImp(this) {
    ConstructOM.constructOM()
    Debug.tieoffDebug(dut.module.debug)
  }
}