/** @file
  Board specific functions in DXE phase to be set as dynamic PCD and consumed by
  commmon platform code.

  Copyright (c) 2009 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "BoardInitDxe.h"

GET_BOARD_NAME mMb3NGetBoardNamePtr = Mb3NGetBoardName;

CHAR16*
EFIAPI
Mb3NGetBoardName (
  IN  UINT8                   BoardId
  )
{
  STATIC CHAR16  BoardName[40];

  DEBUG ((EFI_D_INFO,  "BoardInitDxe: GetBoardName - Minnow Board v3 Next\n"));

  UnicodeSPrint (BoardName, sizeof (BoardName), L"Minnow Board v3 Next (0x%02X)", BoardId);

  if (BoardId != (UINT8) BOARD_ID_MINNOW_NEXT) {
    return NULL;
  } else {
    return BoardName;
  }
}


/**
  Set PCDs for board specific functions.

  @param[in]  ImageHandle   ImageHandle of the loaded driver.
  @param[in]  SystemTable   Pointer to the EFI System Table.

  @retval     EFI_SUCCESS   The handlers were registered successfully.

**/
EFI_STATUS
EFIAPI
Mb3NBoardInitDxeConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINT8       BoardId;

  BoardId = PcdGet8 (PcdBoardId);
  if (BoardId != (UINT8) BOARD_ID_MINNOW_NEXT) {
    return EFI_SUCCESS;
  }

  PcdSet64 (PcdGetBoardNameFunc, (UINT64) mMb3NGetBoardNamePtr);

  return EFI_SUCCESS;
}

